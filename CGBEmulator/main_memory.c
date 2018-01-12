//
//  main_memory.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include <stdlib.h>
#include "main_memory.h"

void initializeMemory(MainMemory *mainMemory) {
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
    return mainMemory->memory[address];
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
