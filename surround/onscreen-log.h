#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <list>
#include <string>
#include "ttf_util.h"

class OnScreenLog {
private:
    std::list<std::string> str_list;
    int max_size, start_y;
    TTF_Font* font = NULL;

public:
    OnScreenLog(TTF_Font* font, int max_size, int start_y) : 
        max_size(max_size), font(font), start_y(start_y) {}

    void add_string(std::string s) {
        this->str_list.push_back(s);
        if(this->str_list.size() > max_size)
            this->str_list.pop_front();
    }

    void render(SDL_Surface* win, int pixels_per_row) {
        int current_offset = this->start_y;
        for(auto s : this->str_list) {
            ::render_text(win, font, s, 10, 
                    current_offset, {122, 122, 122});
            current_offset += pixels_per_row;
        }
    }

};

