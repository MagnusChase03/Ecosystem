#ifndef WindowH
#define WindowH

#include <SDL2/SDL.h>
#include <vector>
#include "GameObjects/Empty.h"
#include "GameObjects/Carrot.h"
#include "GameObjects/Water.h"
#include "GameObjects/Bunny.h"

class Window {

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        std::vector<std::vector<GameObject>> board;
        std::vector<Bunny> bunnies;
        bool run = false;

    public:
        Window();
        void events();
        void update();
        void render();

        bool isRunning() {return run;}

};

#endif