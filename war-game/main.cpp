#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>

#include "TypeRedefines.h"
#include "EventHandling.h"
#include "ColorPack.h"
#include "RenderHelp.h"

using namespace std;

// simple file loading utility
SDL_Texture* loadImageFromFile(const string& filename, SDL_Renderer* ren);
static bool mainLoopQuit = false;
int mouse_x = 0, mouse_y = 0;
int screen_w, screen_h;

class ButtonHandler : public EventHandlerInterface {
private:
    // implemented virtual functions
    void KeyboardButtonDown(SDL_Event& sdle) { mainLoopQuit = true; }
    void KeyboardButtonUp(SDL_Event& sdle) { return; }
    void MouseButtonDown(SDL_Event& sdle) { return; }
    void MouseButtonUp(SDL_Event& sdle) { return; }
    void DefaultCallback(SDL_Event& sdle) { return; }

    void MouseMovement(SDL_Event& sdle) {
        mouse_x = sdle.motion.x;
        mouse_y = sdle.motion.y;
    }

};

int main(int argc, char* argv[]) {
    // quick error check
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Error intializing SDL2\n    " << SDL_GetError() << endl;
        return -1;
    }

    // JPEG and PNG support, SDL_image supports BMP by default
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Window* win = SDL_CreateWindow("Hello World", 100, 100, 640, 480,
            SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL); // various flags
    if(win == 0x00) {
        cerr << "Error creating SDL window\n    " << SDL_GetError() << endl;
        return -1;
    }

    // get the screen size
    SDL_GetWindowSize(win, &screen_w, &screen_h);

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == 0x00) {
        cerr << "Error creating SDL renderer\n    " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Texture* MAP = loadImageFromFile("skyrim-map.jpg", ren);
    ButtonHandler bh;

    int x_offset = 0, y_offset = 0;
    SDL_Rect img_chunk;
    img_chunk.h = screen_h;
    img_chunk.w = screen_w;

    while(!mainLoopQuit) {
        // keyboard update
        bh.update();

        // render sequence
        SDL_RenderClear(ren);

        // draw images onscreen
        Render::axisAlignedImageFullscreen(ren, MAP);
        img_chunk.x = x_offset;
        img_chunk.y = y_offset;
        Render::imageSubsetFullscreen(ren, MAP, img_chunk);

        SDL_RenderPresent(ren); // replacement for SLD_Flip()

        x_offset+=2; y_offset+=1;

        if(x_offset > 2000) {
            x_offset = 0;
            y_offset = 0;
        }
    }

    // free system resources associated with SDL_*
    IMG_Quit();
    SDL_Quit();

    return 0;
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







