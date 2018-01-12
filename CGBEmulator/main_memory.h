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

byte fetchByte(word *programCounter, MainMemory *mainMemory);
word fetchWord(word *programCounter, MainMemory *mainMemory);

void pop(byte  *mostSigByte, byte  *leastSigByte, word *stackPointer, MainMemory *mainMemory);
void push(byte  *mostSigByte, byte  *leastSigByte, word *stackPointer, MainMemory *mainMemory);
void push_16bit_address(word address, word *stackPointer, MainMemory *mainMemory);

byte readByteWithAddress(word address, MainMemory *mainMemory);
byte readByteWithRegs(byte  *mostSigByte, byte  *leastSigByte, MainMemory *mainMemory);

void writeByte(word address, byte data, MainMemory *mainMemory);
void writeWord(word address, word word, MainMemory *mainMemory);

#endif /* main_memory_h */
