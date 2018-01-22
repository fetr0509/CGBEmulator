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
#include "../include/SDL2/SDL.h"

byte isStopped;
byte isHalted;
byte intEnabled;
word cycles;

int main(int argc, char * argv[]) {
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
        //cout << "Something went wrong! " << SDL_GetError() << endl;
    }

    SDL_Window* window = SDL_CreateWindow("SDL_Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          1280, 720, SDL_WINDOW_OPENGL);
    if(window == 0){
        //cout << "Something also went wrong here" << endl;
    }

    SDL_Delay(2000);
    SDL_Quit();
    return 0;
}
