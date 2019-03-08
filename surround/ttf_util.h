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
    int pt_sz = 64;
    
    int last_pixel_size;


    // try at most 100 times. no point in tying 
    // up system resources forever
    for(int i = 0; i < 100; i++) {

        TTF_Font* font_file =  TTF_OpenFont(filename.c_str(), pt_sz);
        last_pixel_size     = TTF_FontHeight(font_file);

        if(last_pixel_size == sz_pixels) {
            return font_file;
        }
        else {

            if(last_pixel_size > sz_pixels) {
                // need smaller pt size
                pt_sz -= 4;
            }
            else {
                // need larger pt size
                pt_sz += 4;
            }

            TTF_CloseFont(font_file);
        }
    }

    return TTF_OpenFont(filename.c_str(), pt_sz);

}
