//
// Created by Peter on 1/24/2018.
//

#include "lcd.h"
#include "constants.h"

void initLCD_Screen(struct LCD_Screen *screen) {
    screen->screenDebugEnabled = 0;

    screen->pixleColors = malloc(sizeof(struct Pixel_Color **));
    screen->pixles = malloc(sizeof(SDL_Rect **));

    (*(screen->pixleColors)) = malloc(sizeof(struct Pixel_Color *) * SCREENSIZE);
    (*(screen->pixles)) = malloc(sizeof(SDL_Rect *) * SCREENSIZE);

    for(int y = 0; y < SCREENSIZE; ++y) {

        (*(screen->pixleColors))[y] = malloc(sizeof(struct Pixel_Color) * SCREENSIZE);
        (*(screen->pixles))[y] = malloc(sizeof(SDL_Rect) * SCREENSIZE);

        for(int x = 0; x < SCREENSIZE; ++x) {
            (*(screen->pixleColors))[y][x].red = 0;
            (*(screen->pixleColors))[y][x].green = 0;
            (*(screen->pixleColors))[y][x].blue = 0;

            (*(screen->pixles))[y][x].x = x*PIXELWIDTH;
            (*(screen->pixles))[y][x].y = y*PIXELWIDTH;
            (*(screen->pixles))[y][x].w = PIXELWIDTH;
            (*(screen->pixles))[y][x].h = PIXELWIDTH;
        }
    }

    return;
}

void drawScreen(SDL_Renderer *gameRenderer, struct LCD_Screen *screen) {
    for (int y = 0; y < SCREENSIZE; ++y) {
        for (int x = 0; x < SCREENSIZE; ++x) {

            byte red = (*(screen->pixleColors))[y][x].red;
            byte green = (*(screen->pixleColors))[y][x].green;
            byte blue = (*(screen->pixleColors))[y][x].blue;

            const SDL_Rect *tempPixel = &(*screen->pixles)[y][x];

            SDL_SetRenderDrawColor(gameRenderer, red, green, blue, 1);
            SDL_RenderFillRect( gameRenderer, tempPixel);
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