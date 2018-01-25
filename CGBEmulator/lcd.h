//
// Created by Peter on 1/24/2018.
//

#ifndef CGBEMULATOR_LCD_H
#define CGBEMULATOR_LCD_H

#include "../include/SDL2/SDL.h"

struct LCD_Screen {
    SDL_Rect **pixles;
};

void initLCD_Screen(struct LCD_Screen *screen);

#endif //CGBEMULATOR_LCD_H
