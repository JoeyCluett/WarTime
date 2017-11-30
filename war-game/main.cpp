#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <glm/glm.hpp>
#include <map>
#include <list>
#include <stdlib.h>

#include <MISC/TimeClass.h>

#include "TypeRedefines.h"
#include "ConstDefines.h"
#include "EventHandling.h"
#include "ColorPack.h"
#include "RenderHelp.h"
#include "ButtonHandler.h"

#include "game/Tile.h"
#include "game/Squad.h"
#include "game/ProjectileRep.h"
#include "game/Animation.h"

using namespace std;

// simple file loading utility
SDL_Texture* loadImageFromFile(const string& filename, SDL_Renderer* ren);
void renderPointer(SDL_Renderer* ren, ColorPack& cp);
void applyAnimations(SDL_Renderer* ren, float deltaT);
bool mainLoopQuit = false;
bool applySquadDamage = false;
int mouse_x = 0, mouse_y = 0;
int screen_w, screen_h;

glm::vec2 start_animation(10.0f, 10.0f);
glm::vec2 end_animation(400.0f, 400.0f);

list<Animation*> animation_list;

// playfield:
vector<vector<Tile>> play_field;

int main(int argc, char* argv[]) {
    // quick error check
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Error intializing SDL2\n    " << SDL_GetError() << endl;
        return -1;
    }

    // JPEG and PNG support, SDL2_image supports BMP by default
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Hello World", 100, 100, 640, 480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); // various flags
    if(win == 0x00) {
        cerr << "Error creating SDL window\n    " << SDL_GetError() << endl;
        return -1;
    }

    // get the screen size
    SDL_GetWindowSize(win, &screen_w, &screen_h);

    // diable cursor
    SDL_ShowCursor(SDL_DISABLE);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == NULL) {
        cerr << "Error creating SDL renderer\n    " << SDL_GetError() << endl;
        return -1;
    }

    // prep random number generator
    srand(time(NULL));

    SDL_Texture* MAP = loadImageFromFile("skyrim-map.jpg", ren);

    GameDataMap gdm;
    gdm[TR::ScreenWidth]  = (void*)&screen_w;
    gdm[TR::ScreenHeight] = (void*)&screen_h;
    gdm[TR::MouseX]       = (void*)&mouse_x;
    gdm[TR::MouseY]       = (void*)&mouse_y;
    gdm[TR::MainLoopQuit] = (void*)&mainLoopQuit;
    gdm[TR::DamageSquad]  = (void*)&applySquadDamage;

    ButtonHandler bh;
    bh.setDataMap(&gdm); // all global game data goes here

    int x_offset = 0, y_offset = 0;
    SDL_Rect img_chunk;
    img_chunk.h = screen_h;
    img_chunk.w = screen_w;

    Tile tile1, tile2;
    tile1.setPosition(1, 1);
    tile2.setPosition(1, 2.05);
    Tile::tile_size = 80.0f;

    Squad squad1(5);
    Squad squad2(5);

    TimeClass tc;
    ProjectileRep pr(end_animation, start_animation, 3.0f, CP::white);
    bool render_projectile = false;
    bool squads_battling = false;
    vector<ProjectileRep> yeet;

    while(!mainLoopQuit) {
        // keyboard update
        bh.update();

        if(applySquadDamage && squad1.size() && squad2.size() && !squads_battling) { // no point in fighting if either party is already dead
            Squad::PrepSkirmish(squad1, squad2, tile1, tile2, CP::blue, CP::red, yeet); // prep battle animation
            squads_battling = true;
        }

        // render sequence
        SDL_RenderClear(ren);
        Render::clearScreen(ren, CP::black);

        tile1.render(ren, CP::grey_lite);
        tile2.render(ren, CP::grey_lite);

        if(squad1.size())
            squad1.render(ren, &tile1, CP::blue);

        if(squad2.size())
            squad2.render(ren, &tile2, CP::red);

        // render battle sequence
        if(squads_battling) {
            double deltaTime = tc.getElapsedSecondsUpdate();
            for(int i = 0; i < yeet.size(); i++) {
                if(yeet[i].render(ren, deltaTime))
                    squads_battling = false;
                //SDL_RenderPresent(ren);
            }

            if(!squads_battling) {
               int s1_size = squad1.size();
               int s2_size = squad2.size();

               for(int i = 0; i < s1_size; i++)
                    squad2.applyDamage(squad1.getTargetIndex(i), 1);
               for(int i = 0; i < s2_size; i++)
                    squad1.applyDamage(squad2.getTargetIndex(i), 1);
               squad1.clean();
               squad2.clean();
            }
        }


        renderPointer(ren, CP::white);
        SDL_RenderPresent(ren); // replacement for SDL_Flip()
        applySquadDamage = false; // RESET for next time around
    }

    // free system resources associated with SDL_*
    IMG_Quit();
    SDL_Quit();

    return 0;
}

void applyAnimations(SDL_Renderer* ren, float deltaT) {
    list<Animation*>::iterator iter = animation_list.begin();
    for(; iter != animation_list.end(); iter++) {
        if((*iter)->render(ren, deltaT))
            iter = animation_list.erase(iter);
    }
}


SDL_Texture* loadImageFromFile(const string& filename, SDL_Renderer* ren) {
    SDL_Surface* sur = IMG_Load(filename.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, sur);
    SDL_FreeSurface(sur);

    if(tex == 0x00) {
        cerr << "Could not load image file: " << filename << endl;
        cerr << "    " << SDL_GetError() << endl;
        exit(1);
    }

    return tex;
}

void renderPointer(SDL_Renderer* ren, ColorPack& cp) {
    Render::cirleHollow(ren, mouse_x, mouse_y, 40, cp);
}





