//
// Created by Peter on 1/24/2018.
//

#include "lcd.h"


void initLCD_Screen(struct LCD_Screen *screen) {
    screen->screenDebugEnabled = 0;

    for (int y = 0; y < 256; ++y) {
        for (int x = 0; x < 256; ++x) {
            SDL_Rect *pixel = malloc(sizeof(SDL_Rect));
            pixel->x = x;
            pixel->y = y;
            pixel->w = 1;
            pixel->h = 1;
            screen->pixles[y][x];
        }
    }
}

void displayTile(struct LCD_Screen *screen, struct LCD_TILE *tile, int tile_X, int tile_Y) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {

        }
    }
}