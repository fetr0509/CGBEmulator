#include "game_loop.h"
#include "main_memory.h"
#include "main_registers.h"
#include "decoder.h"
#include "constants.h"
#include "lcd.h"

static SDL_Window *gameWindow;
static SDL_Renderer *gameRenderer;

static struct LCD_Screen *screen;

void gameLoop();

void startGameLoop(SDL_Window* window, SDL_Renderer* renderer){
    gameWindow = window;
    gameRenderer = renderer;

    screen = malloc(sizeof(struct LCD_Screen));
    initLCD_Screen(screen);

    gameLoop();
}

void gameLoop() {
    int EXIT = 0;

    MainMemory memory;
    MainRegisters registers;

    initializeMemory(&memory);
    initializeMainRegisters(&registers);

    loadROMFromFile(&memory,"Tetris (World).gb");
    dumpVRAMTiles(&memory,screen->pixleColors);

    while(!EXIT) {

        drawScreen(gameRenderer,screen);

        byte opcode = fetchByte(&registers.programCounter,&memory);
        decodeInstruction(opcode,&registers,&memory);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                EXIT = 1;

            SDL_Delay(1);
        }
    }
}