#pragma once

typedef unsigned int u32_t;
typedef int i32_t;
typedef unsigned long long u64_t;

namespace color { 
    u32_t red, green, blue, white, black;
    u32_t dark_red, dark_green, dark_blue; 

    u32_t maroon, yellow, olive, lime;
    u32_t aqua, teal, navy, fuschia;
    u32_t purple;

    u32_t light_grey, dark_grey;

    namespace type {

        u32_t barrier_unknown, barrier_known;
        u32_t field_unknown,   field_known;
        u32_t water_unknown,   water_known;
    
    } // end of namespace type

} // end of namespace color

enum class entity_direction_t : int {
    none, up, down, left, right
};

struct entity_t {
    int x_pos = 0, y_pos = 0; // tile position, screen coords are calculated at runtime
    entity_direction_t dir;
    float visible_radius = 3.0f; // how much of the field is seen by this entity
    float jump_radius    = 1.0f; // units / second
    float attack_radius  = 2.0f; // how many tiles away can this entity attack an enemy

    static int entity_index;
    static std::map<entity_t*, int> global_map;

    // certain functions need to be overloaded
    virtual void render(SDL_Surface* win, float screen_x, float screen_y, float screen_scale, float delta_time) = 0;
};

std::map<entity_t*, int> entity_t::global_map;
int entity_t::entity_index = 0;

struct tile_t {
    // if there is an entity occupying this tile, record its address here
    entity_t* entity_ptr = NULL;
    
    // for SDL rendering system
    u32_t unknown_color;
    u32_t known_color;
    bool known = false;

    u32_t color(void) { return (this->known ? this->known_color : this->unknown_color); }

} __attribute__((packed));


std::array<std::array<tile_t, 100>, 100> g_field; // g_field[y][x]

float map_float(float input, float input_start,  
        float input_end, float output_start, float output_end) {
    return output_start 
            + ((output_end - output_start) 
            / (input_end - input_start)) 
            * (input - input_start);}

