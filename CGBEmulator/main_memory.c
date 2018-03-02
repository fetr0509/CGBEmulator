//
//  main_memory.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include "main_memory.h"

#define ROMSIZE 0x07FFF

void initializeMemory(MainMemory *mainMemory) {

}

void loadROMFromFile(MainMemory *memory, char* filePath) {

    word ROMAddress = 0x0000;
    FILE *ROM;
    byte  buffer;
    
    ROM = fopen(filePath,"rb");  // r for read, b for binary
    
    while (fread(&buffer, sizeof(byte), 1, ROM)) {
        memory->memory[ROMAddress++] = buffer;
    }
}

byte fetchByte(word *programCounter, MainMemory *mainMemory) {
    byte newByte = mainMemory->memory[*programCounter];
    (*programCounter)++;
    return newByte;
}

word fetchWord(word *programCounter, MainMemory *mainMemory) {
    word newByte = mainMemory->memory[*programCounter];
    (*programCounter)++;
    newByte =  newByte | (mainMemory->memory[*programCounter] << 8);
    (*programCounter)++;
    return newByte;
}

void pop(byte  *mostSigByte, byte  *leastSigByte, word *stackPointer, MainMemory *mainMemory) {
    *leastSigByte = mainMemory->memory[(*stackPointer)];
    *mostSigByte = mainMemory->memory[(*stackPointer)+1];
    (*stackPointer)+=2;
}

void popWord(word *value, word *stackPointer, MainMemory *mainMemory){
    *value = (word)(mainMemory->memory[(*stackPointer)]);
    *value = (word)(mainMemory->memory[(*stackPointer)+1]) << 8;
    (*stackPointer)+=2;
}

void push(byte  *mostSigByte, byte  *leastSigByte, word *stackPointer, MainMemory *mainMemory) {
    mainMemory->memory[(*stackPointer)-2] = *leastSigByte;
    mainMemory->memory[(*stackPointer)-1] = *mostSigByte;
    (*stackPointer)-=2;
}

void push_16bit_address(word address, word *stackPointer, MainMemory *mainMemory) {
    mainMemory->memory[(*stackPointer)-2] = (byte)(address & 0xFF);
    mainMemory->memory[(*stackPointer)-1] = (byte)(address >> 8);
    (*stackPointer)-=2;
}

byte readByteWithAddress(word address, MainMemory *mainMemory) {
    byte temp = mainMemory->memory[address];
    return temp;
}

byte readByteWithRegs(byte  *mostSigByte, byte  *leastSigByte, MainMemory *mainMemory) {
    word address = (word)(*mostSigByte);
    address = (address << 8) | (word)(*leastSigByte);
    return mainMemory->memory[address];
}

void writeByte(word address, byte data, MainMemory *mainMemory) {
    mainMemory->memory[address] = data;
}

void writeWord(word address, word data, MainMemory *mainMemory) {
    mainMemory->memory[address] = ((byte)data);
    mainMemory->memory[address+1] = ((byte)((data) >> 8));
}

void convertBytestoTile(const int x, const int y, byte data[16], struct Pixel_Color ***pixleColors) {
    byte currentByte = 0;
    for (int currentY = y; currentY < y + 8; ++currentY) {
        byte currentBit = 1 << 7;

        for (int currentX = x; currentX < x + 8; ++currentX) {
            byte firstByte = data[currentByte++];
            byte secondbyte = data[currentByte++];

            if(firstByte & secondbyte & (currentBit)) {
                (*pixleColors)[currentY][currentX].red = (byte)256;
                (*pixleColors)[currentY][currentX].green = (byte)256;
                (*pixleColors)[currentY][currentX].blue = (byte)256;
            }
            else if (firstByte & currentBit) {
                (*pixleColors)[currentY][currentX].red = (byte)170;
                (*pixleColors)[currentY][currentX].green = (byte)170;
                (*pixleColors)[currentY][currentX].blue = (byte)170;
            }
            else if (secondbyte & currentBit) {
                (*pixleColors)[currentY][currentX].red = (byte)85;
                (*pixleColors)[currentY][currentX].green = (byte)85;
                (*pixleColors)[currentY][currentX].blue = (byte)85;
            }
            else {
                (*pixleColors)[currentY][currentX].red = (byte)0;
                (*pixleColors)[currentY][currentX].green = (byte)0;
                (*pixleColors)[currentY][currentX].blue = (byte)0;
            }
            currentBit >>= 1;
        }
    }
}

void dumpVRAMTiles(MainMemory *memory, struct Pixel_Color ***pixleColors) {
    int currentAddress = 0x8000;
    int x = 0;
    int y = 0;

    byte tile[16];

    while (currentAddress <= 0x8FFF) {

        for(int byteNumber = 0; byteNumber < 16; ++byteNumber) {
            tile[byteNumber] = readByteWithAddress(currentAddress++,memory);
        }

        convertBytestoTile(x,y,tile,pixleColors);

        x += 8;
        if (x == SCREENSIZE) {
            y += 8;
            x = 0;
        }
    }
}
