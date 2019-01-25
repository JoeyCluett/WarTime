#pragma once

#include <iostream>
#include <array>
#include <SDL/SDL.h>
#include "tile.h"

namespace color { 
    u32_t red, green, blue, white, black;
    u32_t dark_red, dark_green, dark_blue; 
} // end of namespace color

std::array<std::array<tile_t, 100>, 100> g_field; // g_field[y][x]

float map_float(float input, float input_start,  
        float input_end, float output_start, float output_end) {
    return output_start 
            + ((output_end - output_start) 
            / (input_end - input_start)) 
            * (input - input_start);}

// for this function, assume the viewport is 
// static and the field moves around it. 
static void render_single_tile(SDL_Surface* win, int x, int y, float screenx, float screeny) {
    //std::cout << "(" << screenx << ", " << screeny << ")\n";

    if(x < 0 || y < 0 || x >= 100 || y >= 100)
        return;

    float pixels_per_tile = win->h / 10.0;

    SDL_Rect r;
    r.h = pixels_per_tile + 1;
    r.w = pixels_per_tile + 1;
    r.x = pixels_per_tile * (float(x) - screenx);
    r.y = pixels_per_tile * (float(y) - screeny);

    //std::cout << "x: " << r.x << ", y: " << r.y 
    //<< ", h: " << r.h << ", w: " << r.w << std::endl;

    SDL_FillRect(win, &r, g_field[y][x].color);
}

// this is the meat of the rendering loop
// this function performs the lookup needed 
// to display the correct things on the field. 
// we (I) know that the screen can display 
// a 10x10 grid of tiles regardless of resolution.
// this function should also prevent excess 
// lookups i.e. it should not try to render 
// EVERY tile if it knows they wont be seen anyway
void render_field(SDL_Surface* win, float screenx, float screeny) {
    int start_x = int(screenx) - 1; // just be sure
    int start_y = int(screeny) - 1; // ...
    int end_x = start_x + 12; // ...
    int end_y = start_y + 12; // ...

    // we have now reduced 10000 possible tiles 
    // to 144. culls > 98% of the field
    for(int y = start_y; y < end_y; y++) {
        for(int x = start_x; x < end_x; x++)
            render_single_tile(win, x, y, screenx, screeny);
    }
}

void initialize_field(void) {
    u32_t c_Arr[] = { color::red, color::green, color::dark_red, color::blue,
            color::dark_green, color::dark_blue, color::black};

    int iter = 0;

    for(int y = 0; y < 100; y++) {
        for(int x = 0; x < 100; x++) {
            tile_t& t = g_field[y][x];
            t.entity.active = false;

            // different colored tiles (rgb)
            t.color = c_Arr[(iter++) % 7];
            //t.color = color::black;
        }
    }
}

SDL_Surface* initialize_window(void) {
    std::cout << "Initializing window...";
    SDL_Init(SDL_INIT_EVERYTHING);
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    int h = info->current_h;
    int w = info->current_w;
    int min = (h < w) ? h : w;

    auto* win = SDL_SetVideoMode(min, min, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    std::cout << "DONE\n";
    return win;
}

void initialize_colors(SDL_Surface* win) {
    std::cout << "Initializing colors...";

    color::white = SDL_MapRGB(win->format, 255, 255, 255);
    color::black = SDL_MapRGB(win->format, 0, 0, 0);

    color::red = SDL_MapRGB(win->format, 255, 0, 0);
    color::green = SDL_MapRGB(win->format, 0, 255, 0);
    color::blue = SDL_MapRGB(win->format, 0, 0, 255);

    color::dark_red = SDL_MapRGB(win->format, 100, 0, 0);
    color::dark_green = SDL_MapRGB(win->format, 0, 100, 0);
    color::dark_blue = SDL_MapRGB(win->format, 0, 0, 100);

    std::cout << "DONE\n";
}


