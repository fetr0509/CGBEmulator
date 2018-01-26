//
//  main.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include <stdio.h>
#include "decoder.h"
#include "constants.h"
#include "game_loop.h"
#include "../include/SDL2/SDL.h"

byte isStopped;
byte isHalted;
byte intEnabled;
word cycles;

int main(int argc, char * argv[]) {
    SDL_Window* window = NULL;
    window = SDL_CreateWindow
            (
                    "CGBEmulator", SDL_WINDOWPOS_UNDEFINED,
                    SDL_WINDOWPOS_UNDEFINED,
                    640,
                    480,
                    SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
            );

    // Setup renderer
    SDL_Renderer* renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    // Clear winow
    SDL_RenderClear( renderer );

    // Start the main game loop.
    startGameLoop(window,renderer);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}
