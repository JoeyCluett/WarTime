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

    ColorPack(void) {
        r = 0x00;
        g = 0x00;
        b = 0x00;
    }

    static ColorPack scale(ColorPack& cp, float s) {
        ColorPack tmp;
        tmp.r = ((float)cp.r) * s;
        tmp.g = ((float)cp.g) * s;
        tmp.b = ((float)cp.b) * s;
        return tmp;
    }

};

namespace CP {

    ColorPack red(255, 0, 0);
    ColorPack green(0, 255, 0);
    ColorPack blue(0, 0, 255);
    ColorPack white(255, 255, 255);
    ColorPack black(0, 0, 0);

    // various shades of grey
    ColorPack grey_lite(200, 200, 200);
    ColorPack grey_med(100, 100, 100);
    ColorPack grey_dark(50, 50, 50);
}

#endif // __JJC__COLOR__PACK__H__
