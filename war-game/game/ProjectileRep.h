#ifndef __JJC__PROJECTILE__REP__H__
#define __JJC__PROJECTILE__REP__H__

#include <glm/glm.hpp>
#include "../ColorPack.h"
#include "../RenderHelp.h"
#include "Tile.h"
#include "Animation.h"

static float animationTransform(float input, float input_start, float input_end, float output_start, float output_end) {
    return (input-input_start)*(output_end-output_start)/(input_end-input_start)+output_start;
}

// projectile representation
// also animates the projectiles
struct ProjectileRep : public Animation {
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
        elapsed_time += (deltaT*2.0f);

        if(elapsed_time >= total_time)
            return true; // animation is finished

        float fT = Tile::tile_size;
        Render::line(ren, start_location.x*fT, start_location.y*fT, end_location.x*fT, end_location.y*fT, color);
  //      Render::circle(ren, fT*current_x, fT*current_y, fT*0.03f, color);

        return false;
    }

};

#endif // __JJC__PROJECTILE__REP__H__
