#pragma once

#include <SDL/SDL.h>
#include <utility>
#include <vector>
#include <map>
#include "util.h"
#include "main.h"

struct regular_squad_entity_t : public entity_t {
    // vector<pair<x, y>>
    const std::vector<std::pair<float, float>> xy_coords = {
        {0.2f, 0.2f}, {0.6f, 0.2f}, {0.4f, 0.4f}, {0.2f, 0.6f}, {0.6f, 0.6f}
    };

    regular_squad_entity_t(int x, int y) {
        this->x_pos = x;
        this->y_pos = y;
        this->dir = entity_direction_t::none;
        this->visible_radius = 5.0f;
        this->jump_radius = 3.0f;
    }

    void render(SDL_Surface* win, float screen_x, float screen_y, float screen_scale, float delta_time) override {
        // this entity doesnt care what direction it is facing. it looks the same all the time
        float pixels_per_tile = win->w / screen_scale;

        SDL_Rect r;
        r.w = pixels_per_tile / 5.0f;
        r.h = pixels_per_tile / 5.0f;

        for(int i : {0, 1, 2, 3, 4}) {
            r.x = pixels_per_tile * (this->x_pos - screen_x + this->xy_coords[i].first);
            r.y = pixels_per_tile * (this->y_pos - screen_y + this->xy_coords[i].second);

            SDL_FillRect(win, &r, color::purple);
        }

    }

};
