//
//  decoder.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "decoder.h"

#define assignInstruction(instruction,op,opType,srcReg,destReg,instrLength,cycleDur) do {\
    instruction->opcode = op; \
    instruction->opcodeType = opType; \
    instruction->sourceReg = srcReg; \
    instruction->destinationReg = destReg; \
    instruction->instructionLength = instrLength; \
    instruction->cycleDuration = cycleDur; \
    } while(0)



uint8_t opcode;
enum OPCODE_TYPE opcodeType;
enum REGISTER sourceReg;
enum REGISTER destinationReg;
uint8_t instructionLength;
uint8_t cycleDuration;

void decodeInstruction(uint8_t opcode, instruction* instruction) {
    
    switch (opcode) {
        case 0x00:
            assignInstruction(instruction,opcode,NOP,NOREG,NOREG,1,4);
            break;
        case 0x10:
            assignInstruction(instruction, opcode, STOP, NOREG, NOREG, 1, 4);
            break;
        case 0x76:
            assignInstruction(instruction, opcode, HALT, NOREG, NOREG, 1, 4);
            break;
        default:
            instruction = NULL;
            break;
    }
    return;
}
