#ifndef __JJC__PROJECTILE__REP__H__
#define __JJC__PROJECTILE__REP__H__

#include <glm/glm.hpp>
#include "../ColorPack.h"
#include "../RenderHelp.h"
#include "Tile.h"

static float animationTransform(float input, float input_start, float input_end, float output_start, float output_end) {
    return (input-input_start)*(output_end-output_start)/(input_end-input_start)+output_start;
}

// projectile representation
// also animates the projectiles
struct ProjectileRep {
    glm::vec2 start_location;
    glm::vec2 end_location;

    float total_time, elapsed_time = 0.0f;
    ColorPack color;

    ProjectileRep(glm::vec2 start_loc, glm::vec2 end_loc, float time, ColorPack& cp) {
        color = cp;
        start_location = start_loc;
        end_location   = end_loc;
        total_time = time;
    }

    // assumes everything that needs to be rendered
    // before this has already been rendered
    bool render(SDL_Renderer* ren, float deltaT) {
        elapsed_time += deltaT;

        if(elapsed_time >= total_time)
            return true; // animation is finished

        bool swapX = false, swapY = false;
        float current_x = 0.0f, current_y = 0.0f;

        // transform x through time:
        if(end_location.x - start_location.x < 0.0f) {
            current_x = -1.0f * animationTransform(elapsed_time, 0.0f, total_time, -1.0f*start_location.x, -1.0f*end_location.x);
        } else {
            current_x = animationTransform(elapsed_time, 0.0f, total_time, start_location.x, end_location.x);
        }

        // transform y through time
        if(end_location.y - start_location.y < 0.0f) {
            current_y = -1.0f * animationTransform(elapsed_time, 0.0f, total_time, -1.0f*start_location.y, -1.0f*end_location.y);
        } else {
            current_y = animationTransform(elapsed_time, 0.0f, total_time, start_location.y, end_location.y);
        }


        float fT = Tile::tile_size;
        Render::line(ren, start_location.x*fT, start_location.y*fT, end_location.x*fT, end_location.y*fT, color);
        Render::circle(ren, fT*current_x, fT*current_y, fT*0.03f, color);

        return false;
    }

};

#endif // __JJC__PROJECTILE__REP__H__
