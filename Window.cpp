#include "Window.h"
#include <ctime>
#include <iostream>

Window::Window(){

    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Ecosystem", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    srand(time(NULL));
    for (int i = 0; i < 60; i++) {

        std::vector<GameObject> objs;
        for (int k = 0; k < 80; k++) {

            double random = rand() % 100;
            if (random < 2) {

                Carrot carrot;
                objs.push_back(carrot);

            } else if (random < 4) {

                Water water;
                objs.push_back(water);

            } else {
            
                Empty empty;
                objs.push_back(empty);
            
            }

        }
        board.push_back(objs);

    }


    for (int i = 10; i < 70; i+= 10) {
    
        Bunny bun(i, 20);
        board[20][i] = bun;
        bunnies.push_back(bun);

        Bunny bum(i, 40);
        board[40][i] = bum;
        bunnies.push_back(bum);
        
    }

    run = true;

}

void Window::events() {

    SDL_Event event;
    SDL_PollEvent(&event);
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    if (event.type == SDL_QUIT) {

        run = false;

    }

    if (event.type == SDL_KEYDOWN) {

        if (keys[SDL_SCANCODE_ESCAPE]) {

            run = false;

        }

    }

}

void Window::update() {

    for (int i = 0; i < bunnies.size(); i++) {

        if (bunnies[i].isAlive()) {

            std::vector<double> spacesNear;
            for (int l = -1; l < 2; l++) {

                for (int k = -1; k < 2; k++) {

                    if (l == 0 && k == 0) {

                        continue;

                    } else {

                        if (bunnies[i].getY() + l < 60 && bunnies[i].getY() + l >= 0 && 
                            bunnies[i].getX() + k < 80 && bunnies[i].getX() + k >= 0) {
                        
                            spacesNear.push_back(board[bunnies[i].getY() + l][bunnies[i].getX() + k].getType());
                        
                        } else {

                            spacesNear.push_back(0);

                        }

                    }

                }

            }

            int action = bunnies[i].getOutput(spacesNear);
            if (action == 0) {

                if (bunnies[i].getY() - 1 < 60 && bunnies[i].getY() - 1 >= 0) {

                    if (board[bunnies[i].getY() - 1][bunnies[i].getX()].getType() != 2) {

                        Empty empty;
                        board[bunnies[i].getY()][bunnies[i].getX()] = empty;
                        board[bunnies[i].getY() - 1][bunnies[i].getX()] = bunnies[i];
                        bunnies[i].setY(bunnies[i].getY() - 1);

                    }

                }

            } else if (action == 1) {

                if (bunnies[i].getY() + 1 < 60 && bunnies[i].getY() + 1 >= 0) {

                    if (board[bunnies[i].getY() + 1][bunnies[i].getX()].getType() != 2) {

                        Empty empty;
                        board[bunnies[i].getY()][bunnies[i].getX()] = empty;
                        board[bunnies[i].getY() + 1][bunnies[i].getX()] = bunnies[i];
                        bunnies[i].setY(bunnies[i].getY() + 1);

                    }

                }

            }  else if (action == 2) {

                if (bunnies[i].getX() - 1 < 80 && bunnies[i].getX() - 1 >= 0) {

                    if (board[bunnies[i].getY()][bunnies[i].getX() - 1].getType() != 2) {

                        Empty empty;
                        board[bunnies[i].getY()][bunnies[i].getX()] = empty;
                        board[bunnies[i].getY()][bunnies[i].getX() - 1] = bunnies[i];
                        bunnies[i].setX(bunnies[i].getX() - 1);
                    
                    }

                }

            }  else if (action == 3) {

                if (bunnies[i].getX() + 1 < 80 && bunnies[i].getX() + 1 >= 0) {

                    if (board[bunnies[i].getY()][bunnies[i].getX() + 1].getType() != 2) {

                        Empty empty;
                        board[bunnies[i].getY()][bunnies[i].getX()] = empty;
                        board[bunnies[i].getY()][bunnies[i].getX() + 1] = bunnies[i];
                        bunnies[i].setX(bunnies[i].getX() + 1);
                    }

                }

            }

            bunnies[i].setHunger(bunnies[i].getHunger() - 1);
            bunnies[i].setThirst(bunnies[i].getThirst() - 1);
            if (bunnies[i].getHunger() == 0 || bunnies[i].getThirst() == 0 ) {

                bunnies[i].setAlive(false);
                Empty empty;
                board[bunnies[i].getY()][bunnies[i].getX()] = empty;

            }
        
        }

    }

}

void Window::render() {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 60; i++) {

        for (int k = 0; k < 80; k++) {

            if (board[i][k].getColor() == "white") {

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            } else if (board[i][k].getColor() == "orange") {

                SDL_SetRenderDrawColor(renderer, 255, 127, 0, 255);

            }  else if (board[i][k].getColor() == "blue") {

                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

            }  else if (board[i][k].getColor() == "pink") {

                SDL_SetRenderDrawColor(renderer, 255, 192, 203, 255);

            }

            SDL_Rect rect;
            rect.x = 10 * k;
            rect.y = 10 * i;
            rect.w = 10;
            rect.h = 10;

            SDL_RenderFillRect(renderer, &rect);

        }

    }

    SDL_RenderPresent(renderer);

}