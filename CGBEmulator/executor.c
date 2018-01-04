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

void handleADDFlags(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    setADDZeroFlag(*regA, *sourceReg, flags);
    clearSubtractionFlag(flags);
    setADD8BitHalfCarryFlag(*regA, *sourceReg, flags);
    setADD8BitCarryFlag(*regA, *sourceReg, flags);
}

void handleSUBFlags(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    setSUBZeroFlag(*regA, *sourceReg, flags);
    setSubtractionFlag(flags);
    setSUB8BitHalfCarryFlag(*regA, *sourceReg, flags);
    setSUB8BitCarryFlag(*regA, *sourceReg, flags);
}

void ADD_8BIT(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    handleADDFlags(regA, sourceReg, flags);
    *regA = *regA + *sourceReg;
}

void ADC(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    uint8_t carry = (*flags >> 4) & 1;
    handleADDFlags(regA, sourceReg + carry, flags);
    *regA = *regA + *sourceReg + carry;
}

void SUB(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    handleSUBFlags(regA, sourceReg, flags);
    *regA = *regA - *sourceReg;
}

void SBC(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    uint8_t carry = (*flags >> 4) & 1;
    handleSUBFlags(regA, sourceReg + carry, flags);
    *regA = *regA - (*sourceReg + carry);
}

void AND(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    if ((*regA & *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    setHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA & *sourceReg;
}

void OR(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    if ((*regA | *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    clearHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA | *sourceReg;
}

void XOR(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    if ((*regA ^ *sourceReg) == 0)
        setZeroFlag(flags);
    clearSubtractionFlag(flags);
    clearHalfCarryFlag(flags);
    clearCarryFlag(flags);
    *regA = *regA ^ *sourceReg;
}

void CP(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags) {
    handleSUBFlags(regA, sourceReg, flags);
}
