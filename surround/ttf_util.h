#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

void render_text(SDL_Surface* win, TTF_Font* f, std::string s, int x, int y, SDL_Color c) {
    SDL_Rect r;
    r.x = x;
    r.y = y;

    auto surf = TTF_RenderText_Solid(f, s.c_str(), c);
    SDL_BlitSurface(surf, NULL, win, &r);
    SDL_FreeSurface(surf);
}

// opens the file multiple times to find a pt size closest to the given pixel size
TTF_Font* open_font_file_to_size(std::string filename, int sz_pixels) {
    int pt_sz_current = 512;
    int pt_sz_diff    = 256;
    int last_pixel_size;

    while(pt_sz_diff >= 1) {

        auto* font_file = TTF_OpenFont(filename.c_str(), pt_sz_current);
        last_pixel_size = TTF_FontHeight(font_file);

        if(last_pixel_size == sz_pixels)
            return font_file;
        else {
            if(last_pixel_size < sz_pixels)
                pt_sz_current += pt_sz_diff;
            else
                pt_sz_current -= pt_sz_diff;

            TTF_CloseFont(font_file);
        }

        pt_sz_diff /= 2;
    }

    return TTF_OpenFont(filename.c_str(), pt_sz_current);
}
