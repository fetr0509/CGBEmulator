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

#define load_8BitRegister_WithRegister(destination, source) ({*destination = *source;})

void load_8BitRegister_With8BitData(uint8_t *destination, uint8_t data);

void ADD_8BIT(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void ADC(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void SUB(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void SBC(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void AND(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void OR(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void XOR(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);
void CP(uint8_t* regA, uint8_t* sourceReg, uint8_t *flags);

#endif /* executor_h */
