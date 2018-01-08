//
//  executor.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/2/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include "executor.h"
#include "constants.h"
#include "flag_helpers.h"

void load_8BitRegister_With8BitData(byte *destination, byte data) {
    *destination = data;
}

void load_16BitRegister_With16BitData(byte  *mostSigByte, byte  *leastSigByte, word data) {
    *mostSigByte = (byte)(data >> 8);
    *leastSigByte = (byte)(data & 0xFF);
}

void jump_address(word  *programCounter, word data) {
    *programCounter = data;
}

void increment_Register(byte *reg) {
    (*reg)++;
}

void increment_RegisterPair(byte  *mostSigByte, byte  *leastSigByte) {
    if (*leastSigByte+1 < *leastSigByte) { // If there is a carry
        (*leastSigByte)++;
        (*mostSigByte)++;
    } else {
        (*leastSigByte)++;
    }
}

void decrement_Register(byte *reg) {
    (*reg)--;
}

void decrement_RegisterPair(byte  *mostSigByte, byte  *leastSigByte) {
    if (*leastSigByte+1 < *leastSigByte) { // If there is a carry
        (*leastSigByte)--;
        (*mostSigByte)--;
    } else {
        (*leastSigByte)--;
    }
}

void handleADDFlags(byte* regA, byte* sourceReg, byte *flags) {
    setADDZeroFlag(*regA, *sourceReg, flags);
    clearSubtractionFlag(flags);
    setADD8BitHalfCarryFlag(*regA, *sourceReg, flags);
    setADD8BitCarryFlag(*regA, *sourceReg, flags);
}

void handleSUBFlags(byte* regA, byte* sourceReg, byte *flags) {
    setSUBZeroFlag(*regA, *sourceReg, flags);
    setSubtractionFlag(flags);
    setSUB8BitHalfCarryFlag(*regA, *sourceReg, flags);
    setSUB8BitCarryFlag(*regA, *sourceReg, flags);
}

void ADD_8BIT(byte* regA, byte* sourceReg, byte *flags) {
    handleADDFlags(regA, sourceReg, flags);
    *regA = *regA + *sourceReg;
}

void ADC(byte* regA, byte* sourceReg, byte *flags) {
    byte carry = (*flags >> 4) & 1;
    handleADDFlags(regA, sourceReg + carry, flags);
    *regA = *regA + *sourceReg + carry;
}

void SUB(byte* regA, byte* sourceReg, byte *flags) {
    handleSUBFlags(regA, sourceReg, flags);
    *regA = *regA - *sourceReg;
}

void SBC(byte* regA, byte* sourceReg, byte *flags) {
    byte carry = (*flags >> 4) & 1;
    handleSUBFlags(regA, sourceReg + carry, flags);
    *regA = *regA - (*sourceReg + carry);
}

void AND(byte* regA, byte* sourceReg, byte *flags) {
    if ((*regA & *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    setHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA & *sourceReg;
}

void OR(byte* regA, byte* sourceReg, byte *flags) {
    if ((*regA | *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    clearHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA | *sourceReg;
}

void XOR(byte* regA, byte* sourceReg, byte *flags) {
    if ((*regA ^ *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    clearHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA ^ *sourceReg;
}

void CP(byte* regA, byte* sourceReg, byte *flags) {
    handleSUBFlags(regA, sourceReg, flags);
}
