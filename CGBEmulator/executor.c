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

void load_RegisterPair_With16BitData(byte  *mostSigByte, byte  *leastSigByte, word data) {
    *mostSigByte = (byte)(data >> 8);
    *leastSigByte = (byte)(data & 0xFF);
}

void load_16BitRegister_With16BitData(word *reg, word data) {
    *reg = data;
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

void decrement_16BitRegister(word  *reg) {
    (*reg)--;
}

void ADD_16BIT(byte  *mostSigByte_dest, byte  *leastSigByte_dest, byte  *mostSigByte_operand, byte  *leastSigByte_operand, byte *flags) {
    clearSubtractionFlag(flags);
    word destination = (((word)*mostSigByte_dest) << 8) | ((word)*leastSigByte_dest);
    word source = (((word)*mostSigByte_operand) << 8) | ((word)*leastSigByte_operand);
    setADD16BitHalfCarryFlag(destination, source, flags);
    setADD16BitCarryFlag(destination, source, flags);
    destination += source;
    *mostSigByte_dest = destination >> 8;
    *leastSigByte_dest = destination & 0xFF;
}

void ADD_16BIT_data(byte  *mostSigByte_dest, byte  *leastSigByte_dest, word data, byte *flags) {
    clearSubtractionFlag(flags);
    word destination = (((word)*mostSigByte_dest) << 8) | ((word)*leastSigByte_dest);
    setADD16BitHalfCarryFlag(destination, data, flags);
    setADD16BitCarryFlag(destination, data, flags);
    destination += data;
    *mostSigByte_dest = destination >> 8;
    *leastSigByte_dest = destination & 0xFF;
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

void complementA(byte *regA) {
    *regA = ~(*regA);
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

void RLC(byte* regA, byte *flags) {
    if((*regA & BIT7) != 0)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
    
    if (*regA == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
    
    clearHalfCarryFlag(flags);
    clearSubtractionFlag(flags);
    
    *regA = (*regA << 1) | (*regA >> 7);
}

void RL(byte* regA, byte *flags) {
    byte tempCarry = CarryFlag(flags);
    if((*regA & BIT7) != 0)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
    
    if (*regA == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
    
    clearHalfCarryFlag(flags);
    clearSubtractionFlag(flags);
    
    *regA = (*regA << 1) | (tempCarry >> 4);
}

void RRC(byte* regA, byte *flags) {
    if((*regA & BIT0) != 0)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
    
    if (*regA == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
    
    clearHalfCarryFlag(flags);
    clearSubtractionFlag(flags);
    
    *regA = (*regA >> 1) | (*regA << 7);
}

void RR(byte* regA, byte *flags) {
    byte tempCarry = *flags & CarryFlag(flags);
    if((*regA & BIT0) != 0)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
    
    if (*regA == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
    
    clearHalfCarryFlag(flags);
    clearSubtractionFlag(flags);
    
    *regA = (*regA >> 1) | (tempCarry << 3);
}

