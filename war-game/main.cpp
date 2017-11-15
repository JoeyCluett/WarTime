#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "EventHandling.h"
#include "RenderHelp.h"

using namespace std;

// simple file loading utility
SDL_Texture* loadImageFromFile(const string& filename, SDL_Renderer* ren);
bool quit = false;

class ButtonHandler : public EventHandlerInterface {
private:
    // implemented virtual functions
    void KeyboardButtonDown(SDL_Event& sdle) { quit = true; }
    void KeyboardButtonUp(SDL_Event& sdle) { return; }
    void MouseButtonDown(SDL_Event& sdle) { return; }
    void MouseButtonUp(SDL_Event& sdle) { return; }
    void DefaultCallback(SDL_Event& sdle) { return; }
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

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(ren == 0x00) {
        cerr << "Error creating SDL renderer\n    " << SDL_GetError() << endl;
        return -1;
    }

    SDL_Texture* FUN = loadImageFromFile("computer-engineer.jpg", ren);
    ButtonHandler bh;

    SDL_Rect rect;
    rect.h = 300; rect.w = 400;
    rect.x = 100; rect.y = 100;

    while(!quit) {
        // keyboard update
        bh.update();

        // render sequence
        SDL_RenderClear(ren);

        // draw images onscreen
        Render::axisAlignedImageFullscreen(ren, FUN);
        //Render::axisAlignedImage(ren, FUN, rect);

        SDL_RenderPresent(ren); // replacement for SLD_Flip()
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







