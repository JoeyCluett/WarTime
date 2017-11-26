#ifndef __JJC__RENDER__HELP__H__
#define __JJC__RENDER__HELP__H__

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "ColorPack.h"

namespace Render {

inline void circle(SDL_Renderer* ren, float x, float y, float radius, ColorPack& cp) {
    filledCircleRGBA(ren, x, y, radius, cp.r, cp.g, cp.b, 255); // always full-alpha
}

inline void cirleHollow(SDL_Renderer* ren, float x, float y, float radius, ColorPack& cp) {
    circleRGBA(ren, x, y, radius, cp.r, cp.g, cp.b, 255);
}

inline void line(SDL_Renderer* ren, float x1, float y1, float x2, float y2, ColorPack& cp) {
    lineRGBA(ren, x1, y1, x2, y2, cp.r, cp.g, cp.b, 255);
}

void axisAlignedBox(SDL_Renderer* ren, SDL_Rect& r, ColorPack& cp) {
    SDL_SetRenderDrawColor(ren, cp.r, cp.g, cp.b, 0xFF);
    SDL_RenderFillRect(ren, &r);
}

void clearScreen(SDL_Renderer* ren, ColorPack& cp) {
    SDL_SetRenderDrawColor(ren, cp.r, cp.g, cp.b, 0xFF);
    SDL_RenderFillRect(ren, NULL);
}

void axisAlignedImage(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect& r) {
    SDL_RenderCopy(ren, tex, NULL, &r);
}

void axisAlignedImageFullscreen(SDL_Renderer* ren, SDL_Texture* tex) {
    SDL_RenderCopy(ren, tex, NULL, NULL);
}

void imageSubsetFullscreen(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect& image_chunk) {
    SDL_RenderCopy(ren, tex, &image_chunk, NULL);
}

// ensure r sits entirely inside SDL_Window
void clampRectToScreen(SDL_Window* win, SDL_Rect& r) {
    int w, h;
    SDL_GetWindowSize(win, &w, &h);

    if(r.w > w || r.h > h) {
        std::cout << "RECT IS LARGER THAN SCREEN\n";
        return; // DO NOT THROW EXCEPTIONS!!!
    }

    if(r.x < 0)
        r.x = 0;

    if(r.y < 0)
        r.y = 0;

    if(r.x+r.w > w)
        r.x = w-r.w;

    if(r.y+r.h > h)
        r.y = h-r.h;
}

// ensure r sits entirely inside SDL_Texture
void clampRectToTexture(SDL_Texture* tex, SDL_Rect& r) {
    int w, h;
    SDL_QueryTexture(tex, NULL, NULL, &w, &h);

    if(r.w > w || r.h > h) {
        std::cout << "RECT IS LARGER THAN TEXTURE\n";
        return;
    }

    if(r.x < 0)
        r.x = 0;

    if(r.y < 0)
        r.y = 0;

    if(r.x+r.w > w)
        r.x = w-r.w;

    if(r.y+r.h > h)
        r.y = h-r.h;

}

} // end of namespace Render::

#endif // __JJC__RENDER__HELP__H__














