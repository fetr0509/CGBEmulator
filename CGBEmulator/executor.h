//
//  executor.h
//  CGBEmulator
//
//  Created by Peter Fetros on 1/2/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#ifndef executor_h
#define executor_h

#include <stdio.h>
#include "constants.h"

#define load_8BitRegister_WithRegister(destination, source) ({*destination = *source;})

void load_8BitRegister_With8BitData(byte *destination, byte data);
void load_RegisterPair_With16BitData(byte  *mostSigByte, byte  *leastSigByte, word data);
void load_16BitRegister_With16BitData(word *reg, word data) ;

void jump_address(word *programCounter, word data);

void increment_Register(byte *reg);
void increment_RegisterPair(byte  *mostSigByte, byte  *leastSigByte);
void increment_16BitRegister(word  *reg);
void decrement_Register(byte *reg);
void decrement_RegisterPair(byte  *mostSigByte, byte  *leastSigByte);
void decrement_16BitRegister(word  *reg);

void ADD_16BIT(byte  *mostSigByte_dest, byte  *leastSigByte_dest, byte  *mostSigByte_operand, byte  *leastSigByte_operand, byte *flags);
void ADD_16BIT_data(byte  *mostSigByte_dest, byte  *leastSigByte_dest, word data, byte *flags);

void complementA(byte *regA);

void ADD_8BIT(byte* regA, byte* sourceReg, byte *flags);
void ADC(byte* regA, byte* sourceReg, byte *flags);
void SUB(byte* regA, byte* sourceReg, byte *flags);
void SBC(byte* regA, byte* sourceReg, byte *flags);
void AND(byte* regA, byte* sourceReg, byte *flags);
void OR(byte* regA, byte* sourceReg, byte *flags);
void XOR(byte* regA, byte* sourceReg, byte *flags);
void CP(byte* regA, byte* sourceReg, byte *flags);

void RLC(byte* regA, byte *flags);
void RL(byte* regA, byte *flags);
void RRC(byte* regA, byte *flags);
void RR(byte* regA, byte *flags);

#endif /* executor_h */
