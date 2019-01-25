#include <iostream>
#include <SDL/SDL.h>
#include <unistd.h>
#include "main.h"

using namespace std;

float window_x = 0.0f, window_y = 0.0f;

int main(int argc, char* argv[]) {

    auto* win = initialize_window();
    initialize_colors(win);
    initialize_field();

    

    usleep(1000000);

    SDL_Quit();
    return 0;
}
