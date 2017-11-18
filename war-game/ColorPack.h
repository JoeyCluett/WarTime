#ifndef __JJC__COLOR__PACK__H__
#define __JJC__COLOR__PACK__H__

#include "TypeRedefines.h"

struct ColorPack {
    u8 r, g, b;

    ColorPack(u8 r, u8 g, u8 b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

};

#endif // __JJC__COLOR__PACK__H__
