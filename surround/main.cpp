#include <iostream>
#include <SDL/SDL.h>
#include <unistd.h>
#include "main.h"

using namespace std;

float window_x = 0.0f, window_y = 0.0f;
float screen_scale = 10.0f;

namespace inputs {

    bool scroll_wheel = false;
    bool scroll_up = false; // doesnt matter unless scroll_wheel is true

    bool left_mouse_clicked = false;
    bool left_mouse_unclicked = false;
    bool right_mouse_clicked = false;
    bool right_mouse_unclicked = false;

    int mouse_x = 0, mouse_y = 0; // fetched once each frame

    // used by move state to track differential movement
    int   move_start_mouse_x = 0;
    int   move_start_mouse_y = 0;
    float move_start_window_x = 0.0f;
    float move_start_window_y = 0.0f;

} // end of namespace inputs

namespace state {

    int current_state;
    const int _default = 0;
    const int _move    = 1;

} // end of namespace state

int main(int argc, char* argv[]) {

    auto* win = initialize_window();
    initialize_colors(win);

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

    bool game_running = true;
    while(game_running) {

        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                // check if we should quit
                case SDL_KEYDOWN:
                    game_running = false;
                    break;
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

        switch(state::current_state) {
            case state::_default:
                if(inputs::scroll_wheel) {
                    if(inputs::scroll_up)
                        screen_scale = screen_scale / 1.1f;
                    else
                        screen_scale = screen_scale * 1.1f;
                    screen_scale = clamp_between(screen_scale, 0.75f, 200.0f);
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

                break;
            case state::_move:
                inputs::scroll_wheel = false; // cant change scale while moving

                if(inputs::left_mouse_unclicked) {
                    state::current_state = state::_default; // back to default state
                    inputs::left_mouse_unclicked = false;

                    // permanently update the viewport coordinates

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
            default:
                SDL_Quit();
                exit(1);
                break;
        }

        // render the field with current settings
        render_field(win, window_x, window_y, screen_scale);
        SDL_Flip(win);
        SDL_Delay(50);
    }

    SDL_Quit();
    
    return 0;
}
