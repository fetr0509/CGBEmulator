//
// Created by Peter on 1/24/2018.
//

#include "lcd.h"


void initLCD_Screen(struct LCD_Screen *screen) {
    screen->screenDebugEnabled = 0;

    screen->pixles = malloc(sizeof(SDL_Rect**) * 256);
    screen->pixleColors = malloc(sizeof(struct Pixel_Color**) * 256);

    for (int y = 0; y < 256; ++y) {
        screen->pixles[y] = malloc(sizeof(SDL_Rect*) * 256);
        screen->pixleColors[y] = malloc(sizeof(struct Pixel_Color*) * 256);

        for (int x = 0; x < 256; ++x) {
            screen->pixleColors[y][x] = malloc(sizeof(struct Pixel_Color*));
            SDL_Rect *pixel = malloc(sizeof(SDL_Rect));
            pixel->x = x;
            pixel->y = y;
            pixel->w = 1;
            pixel->h = 1;
            screen->pixles[y][x] = pixel;
        }
    }
}

void drawScreen(SDL_Renderer *gameRenderer, struct LCD_Screen *screen) {
    for (int y = 0; y < 256; ++y) {
        for (int x = 0; x < 256; ++x) {
            SDL_SetRenderDrawColor(gameRenderer,
                                   screen->pixleColors[y][x]->red,
                                   screen->pixleColors[y][x]->green,
                                   screen->pixleColors[y][x]->blue, 1);
            SDL_RenderFillRect( gameRenderer, screen->pixles[y][x]);
        }
    }
    SDL_RenderPresent(gameRenderer);
}

void loadTile(struct LCD_Screen *screen, struct LCD_TILE *tile, int tile_X, int tile_Y) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {

        }
    }
}