#include "Window.h"

int main() {

    Window *window = new Window();

    int frameDelay = 1000 / 120;
    Uint32 start;
    Uint32 time;
    int ticks = 0;

    while (window->isRunning()) {

        start = SDL_GetTicks();

        window->events();

        if (ticks == 24) {
        
            window->update();
            window->render();
            ticks = 0;
        
        } else {
            
            ticks++;

        }

        time = SDL_GetTicks() - start;
        if (frameDelay > time) {

            SDL_Delay(frameDelay - time);

        }

    }

    return 0;

}