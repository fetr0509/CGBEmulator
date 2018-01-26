//
// Created by Peter on 1/23/2018.
//

#include "game_loop.h"
#include "main_memory.h"
#include "main_registers.h"
#include "decoder.h"
#include "constants.h"

static SDL_Window* gameWindow;
static SDL_Renderer* gameRenderer;

void gameLoop();

void startGameLoop(SDL_Window* window, SDL_Renderer* renderer){
    gameWindow = window;
    gameRenderer = renderer;

    gameLoop();
}

void gameLoop() {
    int EXIT = 0;
    while(!EXIT) {

        SDL_Event Event;
        while(SDL_PollEvent(&Event))
        {
            SDL_Delay(1);
        }
    }
}