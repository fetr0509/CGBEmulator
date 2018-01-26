//
// Created by Peter on 1/24/2018.
//

#ifndef CGBEMULATOR_LCD_H
#define CGBEMULATOR_LCD_H

#include "constants.h"
#include "../include/SDL2/SDL.h"

struct LCD_Screen {
    int screenDebugEnabled;
    SDL_Rect **pixles;
};

void initLCD_Screen(struct LCD_Screen *screen);
void resizeScreen(struct LCD_Screen *screen, int height, int width);
void displayTile(struct LCD_Screen *screen, struct LCD_TILE *tile, int tile_X, int tile_Y);

#endif //CGBEMULATOR_LCD_H
