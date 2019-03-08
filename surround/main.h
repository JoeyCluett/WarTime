#pragma once

#include <iostream>
#include <array>
#include <utility>
#include <SDL/SDL.h>     // rendering library
#include <SDL/SDL_ttf.h> // font library (text)

#include <xml/wrapper/XmlDocument.h>
#include <xml/wrapper/XmlNode.h>

#include "util.h"

inline float clamp_between(float in, float min, float max) {
    if(in < min) {
        return min;
    }
    else if(in > max) {
        return max;
    }
    else {
        return in;
    }
}

void initialize_ttf() {
    std::cout << "Initializing font library...";
    if(TTF_Init() < 0) {
        throw std::runtime_error("Unable to initialize font library");
    }

    std::cout << "DONE\n";
}

// fill every map tile with default color
static void fill_field_default(u32_t unknown_color, u32_t known_color) {
    for(int y = 0; y < 100; y++) {
        for(int x = 0; x < 100; x++) {
            g_field[y][x].unknown_color = unknown_color;
            g_field[y][x].known_color = known_color;
        }
    }
}

static void fill_single_tile(int x, int y, u32_t unknown_c, u32_t known_c) {
    if(x >= 0 && x < 100 && y >= 0 && y < 100) {
        g_field[y][x].unknown_color = unknown_c;
        g_field[y][x].known_color = known_c;
    }
}

// for this function, assume the viewport is 
// static and the field moves around it (which is true)
static void render_single_tile(SDL_Surface* win, int x, int y, float screenx, float screeny, float screen_scale = 10.0f) {

    if(x < 0 || y < 0 || x >= 100 || y >= 100)
        return;

    float pixels_per_tile = win->h / screen_scale;

    SDL_Rect r;
    r.h = pixels_per_tile + 1;
    r.w = pixels_per_tile + 1;
    r.x = pixels_per_tile * (float(x) - screenx);
    r.y = pixels_per_tile * (float(y) - screeny);

    SDL_FillRect(win, &r, g_field[y][x].color());
}

// debug function. its useful to be able to see what tile exactly is being targeted
void render_selected_tile(SDL_Surface* win, int x, int y, float screenx, float screeny, float screen_scale) {
    float pixels_per_tile = win->h / screen_scale;

    SDL_Rect r;
    r.h = pixels_per_tile * 1.0f;
    r.w = pixels_per_tile * 0.1f;
    r.x = pixels_per_tile * (float(x) - screenx);
    r.y = pixels_per_tile * (float(y) - screeny);
    SDL_FillRect(win, &r, color::red);

    r.x = pixels_per_tile * (float(x) - screenx + 0.9f);
    SDL_FillRect(win, &r, color::red);

    r.h = pixels_per_tile * 0.1f;
    r.w = pixels_per_tile * 1.0f;
    r.x = pixels_per_tile * (float(x) - screenx);
    r.y = pixels_per_tile * (float(y) - screeny);
    SDL_FillRect(win, &r, color::red);

    r.y = pixels_per_tile * (float(y) - screeny + 0.9f);
    SDL_FillRect(win, &r, color::red);
}

void render_selected_area(SDL_Surface* win, float screen_x, float screen_y, float screen_scale, 
        int start_x, int start_y, int end_x, int end_y) {
    float pixels_per_tile = win->h / screen_scale;

    int real_start_x = (start_x < end_x) ? start_x : end_x;
    int real_start_y = (start_y < end_y) ? start_y : end_y;
    float height = std::abs(start_y - end_y);
    float width  = std::abs(start_x - end_x);

    SDL_Rect r;

    // render the two horizontal lines
    r.x = pixels_per_tile * (real_start_x - screen_x);
    r.y = pixels_per_tile * (real_start_y - screen_y);
    r.h = pixels_per_tile * 0.2f;
    r.w = pixels_per_tile * width;
    SDL_FillRect(win, &r, color::red);

    r.y = pixels_per_tile * (real_start_y - screen_y + height - 0.2f);
    SDL_FillRect(win, &r, color::red);

    // render the two vertical lines
    r.y = pixels_per_tile * (real_start_y - screen_y);
    r.h = pixels_per_tile * height;
    r.w = pixels_per_tile * 0.2f;
    SDL_FillRect(win, &r, color::red);

    r.x = pixels_per_tile * (real_start_x - screen_x + width - 0.2f);
    SDL_FillRect(win, &r, color::red);
}

// this is the meat of the rendering loop
// this function performs the lookup needed 
// to display the correct things on the field. 
// This function also prevents excessive 
// lookups i.e. it does not try to render 
// EVERY tile if it knows they wont be seen anyway
void render_field(SDL_Surface* win, float screenx, float screeny, float screen_scale = 10.0f) {
    int start_x = int(screenx) - 1; // just be sure
    int start_y = int(screeny) - 1; // ...
    int end_x = start_x + (screen_scale + 3); // ...
    int end_y = start_y + (screen_scale + 3); // ...

    SDL_FillRect(win, NULL, 0);

    // if screen_scale == 10, this method culls approx. 98% of the tiles
    for(int y = start_y; y < end_y; y++) {
        for(int x = start_x; x < end_x; x++)
            ::render_single_tile(win, x, y, screenx, screeny, screen_scale);
    }

    // can be a little more optimized but this will need to suffice
    for(int y = start_y; y < end_y; y++) {
        float fy = y;
        float pixels_per_tile = win->h / screen_scale;

        SDL_Rect r;
        r.h = 1;
        r.w = win->w;
        r.x = 0;
        r.y = pixels_per_tile * (fy - screeny);

        SDL_FillRect(win, &r, color::black);
    }

     for(int x = start_x; x < end_x; x++) {
        float fx = x;
        float pixels_per_tile = win->w / screen_scale;

        SDL_Rect r;
        r.h = win->h;
        r.w = 1;
        r.x = pixels_per_tile * (fx - screenx);
        r.y = 0;

        SDL_FillRect(win, &r, color::black);
    }

}

// helper function to place specific colored blocks 
// on the field from an XML node (map description file)
static void place_map_from_xml_node(XmlNode& n, u32_t unknown_color, u32_t known_color) {
    int x, y, h, w;
    std::string tp = "default";
    
    x = std::stoi(n.attr("x").value());
    y = std::stoi(n.attr("y").value());

    {
        auto a = n.attr("type");
        if(!a.empty())
            tp = a.value();
    }

    if(tp == "rectangular" || tp == "default" || tp == "rect") {
        int h = std::stoi(n.attr("h").value());
        int w = std::stoi(n.attr("w").value());

        for(int j = y; j < (y+h); j++) {
            for(int i = x; i < (x+w); i++)
                ::fill_single_tile(i, j, unknown_color, known_color);
        }

    }
    else if(tp == "circular" || tp == "circle" || tp == "circ") {
        
        int r = std::stoi(n.attr("r").value());
        float r2 = r*r;
        
        auto dist = [](float x0, float y0, float x1, float y1) -> float {
            float x_delt = x1 - x0;
            float y_delt = y1 - y0;

            return (x_delt*x_delt) + (y_delt*y_delt);
        };

        for(int j = (y-r); j < (y+r); j++) {
            for(int i = (x-r); i < (x+r); i++) {
                if(dist(x, y, i, j) <= r2)
                    ::fill_single_tile(i, j, unknown_color, known_color);
            }
        }
    }
}

void initialize_field(std::string filename = "") {
    if(filename == "") {
        u32_t c_Arr[] = { color::red, color::green, color::dark_red, color::blue,
                color::dark_green, color::dark_blue, color::black};

        int iter = 0;
        srand(time(NULL));

        for(int y = 0; y < 100; y++) {
            for(int x = 0; x < 100; x++) {
                tile_t& t = g_field[y][x];

                // different colored tiles (rgb)
                //t.color = c_Arr[(iter++) % 7];
                t.unknown_color = c_Arr[rand() % 7];
                t.known = false;
            }
        }
    } else {
        // test if file is xml or binary format
        if(filename.size() >= 5) {
            // potentially xml. pop three characters off the end
            std::string tmp;
            for(int i : {0, 1, 2}) {
                tmp.push_back(filename.back());
                filename.pop_back();
            }

            // lmx because the characters are reversed
            if(tmp == "lmx") {
                // this is an xml file. use RapidXML and xmlwrapper utility
                filename += "xml"; // add the chars back

                std::cout << "Generating map from XML file...";
                ::fill_field_default(color::dark_green, color::lime);

                XmlDocument doc(filename);

                //std::cout << doc << std::endl;

                auto root = doc.root();

                std::map<std::string, std::pair<u32_t, u32_t>> color_map = {
                    {"barrier", {color::type::barrier_unknown, color::type::barrier_known}},
                    {"field",   {color::type::field_unknown, color::type::field_known}},
                    {"spawn",   {color::white, color::white}},
                    {"water",   {color::type::water_unknown, color::type::water_known}},
                };

                auto n = root.child();
                while(!n.empty()) {

                    try {
                        auto c = color_map.at(n.name());
                        ::place_map_from_xml_node(n, c.first, c.second);
                    } catch(std::exception& err) {
                        throw std::runtime_error("Error when generating map from XML file: " + std::string(err.what()));
                    }

                    n = n.next();
                }

                std::cout << "DONE\n";

            } else {
                // this is a binary file
                std::cout << "Binary files are not yet supported...\n";
                exit(1);
            }
        }
    }
}

SDL_Surface* initialize_window(void) {
    std::cout << "Initializing window...";
    SDL_Init(SDL_INIT_EVERYTHING);
    const SDL_VideoInfo* info = SDL_GetVideoInfo();
    int h = info->current_h;
    int w = info->current_w;
    int min = (h < w) ? h : w;

    auto* win = SDL_SetVideoMode(min, min, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    std::cout << "DONE\n";
    return win;
}

void initialize_colors(SDL_Surface* win) {
    std::cout << "Initializing colors...";

    auto f = win->format;

    color::white = SDL_MapRGB(win->format, 255, 255, 255);
    color::black = SDL_MapRGB(win->format, 0, 0, 0);
    color::red   = SDL_MapRGB(win->format, 255, 0, 0);
    color::green = SDL_MapRGB(win->format, 0, 0x80, 0);
    color::blue  = SDL_MapRGB(win->format, 0, 0, 255);

    color::dark_red   = SDL_MapRGB(win->format, 100, 0, 0);
    color::dark_green = SDL_MapRGB(win->format, 0, 80, 0);
    color::dark_blue  = SDL_MapRGB(win->format, 0, 0, 100);

    color::maroon  = SDL_MapRGB(f, 0x80, 0x00, 0x00);
    color::yellow  = SDL_MapRGB(f, 0xFF, 0xFF, 0x00);
    color::olive   = SDL_MapRGB(f, 0x80, 0x80, 0x00);
    color::lime    = SDL_MapRGB(f, 0x00, 0xFF, 0x00);
    color::aqua    = SDL_MapRGB(f, 0x00, 0xFF, 0xFF);
    color::teal    = SDL_MapRGB(f, 0x00, 0x80, 0x80);
    color::navy    = SDL_MapRGB(f, 0x00, 0x00, 0x80);
    color::fuschia = SDL_MapRGB(f, 0xFF, 0x00, 0xFF);
    color::purple  = SDL_MapRGB(f, 0x80, 0x00, 0x80);

    color::light_grey = SDL_MapRGB(f, 120, 120, 120);
    color::dark_grey  = SDL_MapRGB(f, 0x49, 0x49, 0x49);

    // specify some special colors here
    color::type::barrier_unknown = color::dark_grey;
    color::type::barrier_known   = color::light_grey;

    color::type::water_unknown   = color::dark_blue;
    color::type::water_known     = color::blue;

    color::type::field_unknown   = color::green;
    color::type::field_known     = color::lime;

    std::cout << "DONE\n";
}


