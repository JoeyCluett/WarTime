#ifndef __JJC__BUTTON__HANDLER__H__
#define __JJC__BUTTON__HANDLER__H__

#include <iostream>
#include "TypeRedefines.h"
#include "ConstDefines.h"
#include "EventHandling.h"

class ButtonHandler : public EventHandlerInterface {
protected:
    // implemented virtual functions
    void KeyboardButtonDown(SDL_Event& sdle) {
        switch(sdle.key.keysym.sym) {
            case SDLK_SPACE: // space
                *retrieve<bool>(TR::DamageSquad) = true;
                break;
            default:
                *retrieve<bool>(TR::MainLoopQuit) = true;
                break;
        }
    }

    void KeyboardButtonUp(SDL_Event& sdle) {
        return;
    }

    void MouseButtonDown(SDL_Event& sdle) {
        return;
    }

    void MouseButtonUp(SDL_Event& sdle) {
        return;
    }

    void DefaultCallback(SDL_Event& sdle) {
        return;
    }

    void MouseMovement(SDL_Event& sdle) {
        *retrieve<>(TR::MouseX) = sdle.motion.x;
        *retrieve<>(TR::MouseY) = sdle.motion.y;
    }
};


#endif // __JJC__BUTTON__HANDLER__H__
