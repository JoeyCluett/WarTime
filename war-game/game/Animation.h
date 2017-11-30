#ifndef __JJC__ANIMATION__H__
#define __JJC__ANIMATION__H__

#include <SDL2/SDL.h>

class Animation {
public:
    virtual bool render(SDL_Renderer* ren, float deltaT) = 0;
};

#endif // __JJC__ANIMATION__H__
