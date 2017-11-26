#ifndef __JJC__EVENT__HANDLING__H__
#define __JJC__EVENT__HANDLING__H__

#include <SDL2/SDL.h>
#include "TypeRedefines.h"

class EventHandlerInterface {
protected:
    // event handler callbacks
    virtual void KeyboardButtonDown(SDL_Event& sdle) = 0;
    virtual void KeyboardButtonUp(SDL_Event& sdle)   = 0;
    virtual void MouseButtonDown(SDL_Event& sdle)    = 0;
    virtual void MouseButtonUp(SDL_Event& sdle)      = 0;
    virtual void MouseMovement(SDL_Event& sdle)      = 0;
    virtual void DefaultCallback(SDL_Event& sdle)    = 0; // for everything else not covered above

    GameDataMap* gdm;

    template<typename T = int> // default type is int
    T* retrieve(int key) {
        return (T*)gdm->at(key);
    }

public:

    void setDataMap(GameDataMap* gdm) {
        this->gdm = gdm;
    }

    // update loop is the same for every EventHandlerInterface
    void update(void) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_KEYDOWN:
                    KeyboardButtonDown(e);
                    break;
                case SDL_KEYUP:
                    KeyboardButtonUp(e);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    MouseButtonDown(e);
                    break;
                case SDL_MOUSEBUTTONUP:
                    MouseButtonUp(e);
                    break;
                case SDL_MOUSEMOTION:
                    MouseMovement(e);
                    break;
                default:
                    DefaultCallback(e);
                    break;
            }
        }
    }
};

#endif // __JJC__EVENT__HANDLING__H__
