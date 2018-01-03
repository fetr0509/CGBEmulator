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

typedef struct MainMemory {
    uint8_t memory[0xFFFF];
} MainMemory;

void initializeMemory(MainMemory* memory);
void loadROMFromFile(MainMemory* memory, char* filePath);

#endif /* main_memory_h */
