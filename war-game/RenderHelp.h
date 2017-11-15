#ifndef __JJC__RENDER__HELP__H__
#define __JJC__RENDER__HELP__H__

#include <SDL2/SDL.h>

typedef uint8_t u8;

struct ColorPack {
    u8 r, g, b;
};

namespace Render {

void axisAlignedBox(SDL_Renderer* ren, SDL_Rect& r, ColorPack& cp) {
    SDL_SetRenderDrawColor(ren, cp.r, cp.g, cp.b, 0xFF);
    SDL_RenderFillRect(ren, &r);
}

void axisAlignedImage(SDL_Renderer* ren, SDL_Texture* tex, SDL_Rect& r) {
    SDL_RenderCopy(ren, tex, NULL, &r);
}

void axisAlignedImageFullscreen(SDL_Renderer* ren, SDL_Texture* tex) {
    SDL_RenderCopy(ren, tex, NULL, NULL);
}

} // end of namespace Render::

#endif // __JJC__RENDER__HELP__H__
