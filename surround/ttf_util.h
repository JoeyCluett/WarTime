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
