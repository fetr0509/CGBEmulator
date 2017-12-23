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
    uint8_t highNibble = opcode >> 4;
    uint8_t lowNibble = opcode & 0xF;
    
    // instruction is either load or arithmetic, but not HALT
    if(0x3 < highNibble && highNibble < 0xC && opcode != 0x76) {
        
        // calculate source register based on numeric pattern in opcode
        enum REGISTER source = ((REG_B) + (lowNibble % NUMREGS));
        
        // instruction is a load
        if (0x3 < highNibble && highNibble < 0x8) {
            // calculate destination register based on different numerical pattern
            enum REGISTER destination = ((REG_B) + ((opcode - 0x40) / 8));
            uint8_t cycleDur = (source == REG_HL || destination == REG_HL) ? 8 : 4;
            assignInstruction(instruction,opcode,LD,source,destination,1,cycleDur);
        }
        
        // instruction is arithmetic
        else {
            uint8_t cycleDur = (source == REG_HL) ? 8 : 4;
            uint8_t arithmeticType = (lowNibble - 0x80) / 8;
            switch (arithmeticType) {
                case 0:
                    assignInstruction(instruction,opcode,ADD,source,REG_A,1,cycleDur);
                    break;
                case 1:
                    assignInstruction(instruction,opcode,ADC,source,REG_A,1,cycleDur);
                    break;
                case 2:
                    assignInstruction(instruction,opcode,SUB,source,REG_A,1,cycleDur);
                    break;
                case 3:
                    assignInstruction(instruction,opcode,SUBC,source,REG_A,1,cycleDur);
                    break;
                case 4:
                    assignInstruction(instruction,opcode,AND,source,REG_A,1,cycleDur);
                    break;
                case 5:
                    assignInstruction(instruction,opcode,XOR,source,REG_A,1,cycleDur);
                    break;
                case 6:
                    assignInstruction(instruction,opcode,OR,source,REG_A,1,cycleDur);
                    break;
                case 7:
                    assignInstruction(instruction,opcode,CP,source,REG_A,1,cycleDur);
                    break;
                default:
                    instruction = NULL;
                    break;
            }
        }
    } else {
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
    }
    return;
}
