//
//  instruction.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/22/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef instruction_h
#define instruction_h

#include <stdio.h>
#include "constants.c"

typedef struct instruction {
    uint8_t opcode;
    enum OPCODE_TYPE opcodeType;
    enum REGISTER sourceReg;
    enum REGISTER destinationReg;
    uint8_t instructionLength;
    uint8_t cycleDuration;
} instruction;

#endif /* instruction_h */
