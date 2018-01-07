//
//  main_memory.h
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#ifndef main_memory_h
#define main_memory_h

#include <stdio.h>
#include "constants.h"

typedef struct MainMemory {
    byte memory[0xFFFF];
} MainMemory;

void initializeMemory(MainMemory *memory);
void loadROMFromFile(MainMemory *memory, char* filePath);

byte fetchtByte(word *programCounter, MainMemory *mainMemory);
word fetchWord(word *programCounter, MainMemory *mainMemory);

byte readByteWithAddress(word address, MainMemory *mainMemory);
byte readByteWithRegs(byte  *mostSigByte, byte  *leastSigByte, MainMemory *mainMemory);

#endif /* main_memory_h */
