#include <iostream>
#include <SDL/SDL.h>
#include <unistd.h>
#include "main.h"
#include "entity.h"
#include "ttf_util.h"

using namespace std;

#define MAX_MS_PER_FRAME 16 // ~60 fps

float window_x = 0.0f, window_y = 0.0f;
float screen_scale = 10.0f;

namespace inputs {
    bool scroll_wheel = false;
    bool scroll_up = false; // doesnt matter unless scroll_wheel is true

    bool left_mouse_clicked    = false;
    bool left_mouse_unclicked  = false;
    bool right_mouse_clicked   = false;
    bool right_mouse_unclicked = false;

    int mouse_x = 0, mouse_y = 0; // screen position of mouse
    float mouse_field_x = 0.0f, mouse_field_y = 0.0f; // mouse position relative to the field

    // used by move state to track differential movement
    int   move_start_mouse_x = 0;
    int   move_start_mouse_y = 0;
    float move_start_window_x = 0.0f;
    float move_start_window_y = 0.0f;

    // used by select state to track which area is selected
    int select_start_x = 0;
    int select_start_y = 0;
    int select_end_x = 0;
    int select_end_y = 0;

} // end of namespace inputs

namespace state {
    int current_state;
    const int _default = 0;
    const int _move    = 1;
    const int _select  = 2;
} // end of namespace state

namespace framerate {
    int start_time;
    int end_time;
    int delta_time;
    std::string fr_string;

    // regardless of framerate, display ms/frame once every 200ms
    int time_since_last_display = 0;
    int display_delta_time = 0; // updated periodically

} // end of namespace framerate

namespace entities {

    std::map<std::string, entity_t*> e_map;

} // end of namespace entities

int main(int argc, char* argv[]) {

    SDL_Surface* win;

    try {
        win = initialize_window();
        initialize_colors(win);
        initialize_ttf();
    } catch(std::exception& err) {
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    // load our favorite font file
    int font_size = win->h / 20;
    auto* font_file = ::open_font_file_to_size("BEBAS___.ttf", font_size);
    if(!font_file) {
        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    if(argc == 2) {
        try {
            initialize_field(argv[1]);
        } catch(exception& err) {
            SDL_Quit();
            cout << endl << err.what() << endl;
            exit(1);
        }
    }
    else {
        initialize_field();
    }

    // first timestamp
    framerate::start_time = SDL_GetTicks();

    auto regular_game_entity = new regular_squad_entity_t(0, 0);

    bool game_running = true;
    while(game_running) {

        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                // check if we should quit
                case SDL_KEYDOWN:
                    game_running = false; break;
                case SDL_MOUSEBUTTONDOWN:
                    switch(ev.button.button) {
                        case SDL_BUTTON_WHEELUP:
                            inputs::scroll_wheel = true;
                            inputs::scroll_up = true;
                            break;
                        case SDL_BUTTON_WHEELDOWN:
                            inputs::scroll_wheel = true;
                            inputs::scroll_up = false;
                            break;
                        case SDL_BUTTON_LEFT:
                            inputs::left_mouse_clicked = true; break;
                        case SDL_BUTTON_RIGHT:
                            inputs::right_mouse_clicked = true; break;
                        default:
                            break;
                    } break;
                case SDL_MOUSEBUTTONUP:
                    switch(ev.button.button) {
                        case SDL_BUTTON_LEFT:
                            inputs::left_mouse_unclicked = true; break;
                        case SDL_BUTTON_RIGHT:
                            inputs::right_mouse_unclicked = true; break;
                        default:
                            break;
                    } break;
                case SDL_MOUSEMOTION:
                    inputs::mouse_x = ev.motion.x;
                    inputs::mouse_y = ev.motion.y;

                    break;
                default: break;
            }
        }

        // calculate the position of the mouse relative to the field
        inputs::mouse_field_x = window_x + map_float(inputs::mouse_x, 0.0f, win->w, 0.0f, screen_scale);
        inputs::mouse_field_y = window_y + map_float(inputs::mouse_y, 0.0f, win->h, 0.0f, screen_scale);

        switch(state::current_state) {
            case state::_default:
                if(inputs::scroll_wheel) {

                    //float tmp_window_x = window_x;
                    //float tmp_window_y = window_y;

                    // center needs to be the same before and after
                    float window_center_x = window_x + (screen_scale / 2.0f);
                    float window_center_y = window_y + (screen_scale / 2.0f);

                    if(inputs::scroll_up)
                        screen_scale = screen_scale / 1.1f;
                    else
                        screen_scale = screen_scale * 1.1f;
                    screen_scale = clamp_between(screen_scale, 0.75f, 200.0f);

                    // recenter the screen around the same point
                    window_x = window_center_x - (screen_scale / 2.0f);
                    window_y = window_center_y - (screen_scale / 2.0f);

                    inputs::scroll_wheel = false;
                }
                
                if(inputs::left_mouse_clicked) {
                    inputs::move_start_mouse_x = inputs::mouse_x;
                    inputs::move_start_mouse_y = inputs::mouse_y;
                    inputs::move_start_window_x = window_x;
                    inputs::move_start_window_y = window_y;
                    
                    state::current_state = state::_move; // change state for next iteration
                    inputs::left_mouse_clicked = false;
                }
                else if(inputs::right_mouse_clicked) {
                    inputs::select_start_x = int(inputs::mouse_field_x);
                    inputs::select_start_y = int(inputs::mouse_field_y);
                    inputs::select_end_x = inputs::select_start_x + 1;
                    inputs::select_end_y = inputs::select_start_y + 1;

                    state::current_state = state::_select;
                    inputs::right_mouse_clicked = false;
                }
                break;
            case state::_move:
                inputs::scroll_wheel = false; // cant change scale while moving

                if(inputs::left_mouse_unclicked) {
                    state::current_state = state::_default; // back to default state
                    inputs::left_mouse_unclicked = false;
                }
                else {
                    int delta_mouse_x = inputs::move_start_mouse_x - inputs::mouse_x;
                    int delta_mouse_y = inputs::move_start_mouse_y - inputs::mouse_y;

                    float delta_mouse_scaled_x = map_float(delta_mouse_x, 0.0f, win->w, 0.0f, screen_scale);
                    float delta_mouse_scaled_y = map_float(delta_mouse_y, 0.0f, win->h, 0.0f, screen_scale);

                    window_x = inputs::move_start_window_x + delta_mouse_scaled_x;
                    window_y = inputs::move_start_window_y + delta_mouse_scaled_y;
                }
                break;
            case state::_select:
                // cant scale while selecting
                inputs::scroll_wheel = false;

                if(inputs::right_mouse_unclicked) {
                    state::current_state = state::_default; // change state back to default
                    inputs::right_mouse_unclicked = false;
                }
                else {
                    // track the area being selected
                    inputs::select_end_x = inputs::mouse_field_x;
                    inputs::select_end_y = inputs::mouse_field_y;
                }

                break;
            default:
                SDL_Quit();
                exit(1);
                break;
        }

        // render the field with current settings
        render_field(win, window_x, window_y, screen_scale);

        if(state::current_state == state::_select) {
            render_selected_area(win, window_x, window_y, screen_scale, 
                inputs::select_start_x, inputs::select_start_y, inputs::select_end_x, inputs::select_end_y);
        }
        else {
            render_selected_tile(win, inputs::mouse_field_x, inputs::mouse_field_y, window_x, window_y, screen_scale);
        }

        regular_game_entity->render(win, window_x, window_y, screen_scale, 0.1f);

        render_text(win, font_file, framerate::fr_string, 20, 0, {150, 150, 150});
        if(framerate::time_since_last_display >= 200) {
            framerate::time_since_last_display -= 200;
            framerate::display_delta_time = framerate::delta_time;
        }

        // show the position of the mouse in world coordinates
        render_text(win, font_file, "x : " + to_string(inputs::mouse_field_x) + ", y : " 
            + to_string(inputs::mouse_field_y), 20, 1 * font_size, {150, 150, 150});

        SDL_Flip(win);

        framerate::end_time = SDL_GetTicks();
        framerate::delta_time = framerate::end_time - framerate::start_time;
        framerate::time_since_last_display += MAX_MS_PER_FRAME;
        framerate::fr_string = "ms/frame:  " + to_string(framerate::display_delta_time);

        if(framerate::delta_time < MAX_MS_PER_FRAME) {
            SDL_Delay(MAX_MS_PER_FRAME - framerate::delta_time);
        }
        framerate::start_time = SDL_GetTicks();
    }

    TTF_CloseFont(font_file);
    SDL_Quit();
    
    return 0;
}
