#ifndef __JJC__TILE__H__
#define __JJC__TILE__H__

#include <SDL2/SDL.h>
#include "../ColorPack.h"
#include "../RenderHelp.h"

enum PlayerColor {
    PlayerColor_None, PlayerColor_Red, PlayerColor_Blue
};

class Tile {
private:
    bool has_combatants = false;
    SDL_Rect r;
    float x = 0.0f, y = 0.0f;
    PlayerColor pc = PlayerColor_None;
public:
    // same for every Tile
    static float tile_size;

    void setPosition(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Tile(void) {
        ;
    }

    Tile(float x, float y) {
        setPosition(x, y);
    }

    float getX(void) { return x; }
    float getY(void) { return y; }

    void render(SDL_Renderer* ren, ColorPack& cp) {
        r.w = tile_size;
        r.h = tile_size;
        r.x = x * tile_size;
        r.y = y * tile_size;

        Render::axisAlignedBox(ren, r, cp);
    }

};

float Tile::tile_size = 100.0f; // initialization of static variable

#endif // __JJC__TILE__H__
