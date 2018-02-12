//
// Created by Peter on 1/24/2018.
//

#ifndef CGBEMULATOR_LCD_H
#define CGBEMULATOR_LCD_H

#include "constants.h"
#include "../include/SDL2/SDL.h"
static SDL_Renderer *gameRenderer;

struct Pixel_Color {
    byte red;
    byte green;
    byte blue;
};

struct LCD_Screen {
    int screenDebugEnabled;
    SDL_Rect ***pixles;
    struct Pixel_Color ***pixleColors;
};

void initLCD_Screen(struct LCD_Screen *screen);
void resizeScreen(struct LCD_Screen *screen, int height, int width);
void drawScreen(SDL_Renderer *gameRenderer,struct LCD_Screen *screen);
void loadTile(struct LCD_Screen *screen, struct LCD_TILE *tile, int tile_X, int tile_Y);

#endif //CGBEMULATOR_LCD_H