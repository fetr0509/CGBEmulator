//
//  decoder.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "decoder.h"

#define assignInstruction(instruction,op,opType,destReg,srcReg,instrLength,cycleDur) do {\
    instruction->opcode = op; \
    instruction->opcodeType = opType; \
    instruction->sourceReg = srcReg; \
    instruction->destinationReg = destReg; \
    instruction->instructionLength = instrLength; \
    instruction->cycleDuration = cycleDur; \
    } while(0)



uint8_t opcode;
enum OPCODE_TYPE opcodeType;
enum REGISTERTYPE sourceReg;
enum REGISTERTYPE destinationReg;
uint8_t instructionLength;
uint8_t cycleDuration;

void decodeInstruction(uint8_t opcode, instruction* instruction) {
    uint8_t highNibble = opcode >> 4;
    uint8_t lowNibble = opcode & 0xF;
    
    // instruction is either load or arithmetic, but not HALT
    if(0x3 < highNibble && highNibble < 0xC && opcode != 0x76) {
        
        // calculate source register based on numeric pattern in opcode
        enum REGISTERTYPE source = ((REG_B) + (lowNibble % NUMREGS));
        
        // instruction is a load
        if (0x3 < highNibble && highNibble < 0x8) {
            // calculate destination register based on different numerical pattern
            enum REGISTERTYPE destination = ((REG_B) + ((opcode - 0x40) / 8));
            uint8_t cycleDur = (source == REG_HL || destination == REG_HL) ? 8 : 4;
            assignInstruction(instruction,opcode,LD,destination,source,1,cycleDur);
        }
        
        // instruction is arithmetic
        else {
            uint8_t cycleDur = (source == REG_HL) ? 8 : 4;
            uint8_t arithmeticType = (lowNibble - 0x80) / 8;
            switch (arithmeticType) {
                case 0:
                    assignInstruction(instruction,opcode,ADD,REG_A,source,1,cycleDur);
                    break;
                case 1:
                    assignInstruction(instruction,opcode,ADC,REG_A,source,1,cycleDur);
                    break;
                case 2:
                    assignInstruction(instruction,opcode,SUB,REG_A,source,1,cycleDur);
                    break;
                case 3:
                    assignInstruction(instruction,opcode,SUBC,REG_A,source,1,cycleDur);
                    break;
                case 4:
                    assignInstruction(instruction,opcode,AND,REG_A,source,1,cycleDur);
                    break;
                case 5:
                    assignInstruction(instruction,opcode,XOR,REG_A,source,1,cycleDur);
                    break;
                case 6:
                    assignInstruction(instruction,opcode,OR,REG_A,source,1,cycleDur);
                    break;
                case 7:
                    assignInstruction(instruction,opcode,CP,REG_A,source,1,cycleDur);
                    break;
                default:
                    instruction = NULL;
                    break;
            }
        }
    } else {
        switch (opcode) {
            case 0x00: // NOP
                assignInstruction(instruction,opcode,NOP,NOREG,NOREG,1,4);
                break;
            case 0x01: // stop
                assignInstruction(instruction,opcode,LD,REG_BC,DATA_16,1,4);
                break;
            case 0x02:
                assignInstruction(instruction,opcode,LD,REG_BC,REG_A,1,8);
                break;
            case 0x03:
            case 0x04:
            case 0x05:
            case 0x06: // LD 8 bit val
                assignInstruction(instruction,opcode,LD,REG_B,DATA_8,2,8);
                break;
            case 0x07:
            case 0x08:
                assignInstruction(instruction,opcode,LD,DATA_16,STACK_POINTER,1,4);
                break;
            case 0x09:
            case 0x0A:
                assignInstruction(instruction,opcode,LD,REG_A,REG_BC,1,8);
                break;
            case 0x0B:
            case 0x0C:
            case 0x0D:
            case 0x0E:
                assignInstruction(instruction,opcode,LD,REG_C,DATA_8,2,8);
                break;
            case 0x0F:
            case 0x10:
            case 0x11:
                assignInstruction(instruction,opcode,LD,REG_DE,DATA_16,1,4);
                break;
            case 0x12:
                assignInstruction(instruction,opcode,LD,REG_DE,REG_A,1,8);
                break;
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
                assignInstruction(instruction,opcode,LD,REG_D,DATA_8,2,8);
                break;
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1A:
                assignInstruction(instruction,opcode,LD,REG_A,REG_DE,1,8);
                break;
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x1E:
                assignInstruction(instruction,opcode,LD,REG_E,DATA_8,2,8);
                break;
            case 0x1F:
            case 0x20:
            case 0x21:
                assignInstruction(instruction,opcode,LD,REG_HL,DATA_16,1,4);
                break;
            case 0x22:
                ssignInstruction(instruction,opcode,LDI,REG_HL,REG_A,1,8);
                break;
            case 0x23:
            case 0x24:
            case 0x25:
            case 0x26:
                assignInstruction(instruction,opcode,LD,REG_H,DATA_8,2,8);
                break;
            case 0x27:
            case 0x28:
            case 0x29:
            case 0x2A:
                assignInstruction(instruction,opcode,LDI,REG_A,REG_HL,1,8);
                break;
            case 0x2B:
            case 0x2C:
            case 0x2D:
            case 0x2E:
                assignInstruction(instruction,opcode,LD,REG_L,DATA_8,2,8);
                break;
            case 0x2F:
            case 0x30:
            case 0x31:
                assignInstruction(instruction,opcode,LD,STACK_POINTER,DATA_16,1,4);
                break;
            case 0x32:
                ssignInstruction(instruction,opcode,LDD,REG_HL,REG_A,1,8);
                break;
            case 0x33:
            case 0x34:
            case 0x35:
            case 0x36:
            case 0x37:
            case 0x38:
            case 0x39:
            case 0x3A:
                assignInstruction(instruction,opcode,LDD,REG_A,REG_HL,1,8);
                break;
            case 0x3B:
            case 0x3C:
            case 0x3D:
            case 0x3E:
                assignInstruction(instruction,opcode,LD,REG_A,DATA_8,1,8);
                break;
            case 0x3F:
            case 0x76: // HALT
            case 0xC0:
            case 0xC1:
            case 0xC2:
            case 0xC3:
            case 0xC4:
            case 0xC5:
            case 0xC6:
            case 0xC7:
            case 0xC8:
            case 0xC9:
            case 0xCA:
            case 0xCB:
            case 0xCC:
            case 0xCD:
            case 0xCE:
            case 0xCF:
            case 0xD0:
            case 0xD1:
            case 0xD2:
            case 0xD3:
            case 0xD4:
            case 0xD5:
            case 0xD6:
            case 0xD7:
            case 0xD8:
            case 0xD9:
            case 0xDA:
            case 0xDB:
            case 0xDC:
            case 0xDD:
            case 0xDE:
            case 0xDF:
            case 0xE0:
                ssignInstruction(instruction,opcode,LDH,DATA_8,REG_A,1,8);
                break;
            case 0xE1:
            case 0xE2:
                assignInstruction(instruction,opcode,LD,REG_C,REG_A,1,8);
                break;
            case 0xE3:
            case 0xE4:
            case 0xE5:
            case 0xE6:
            case 0xE7:
            case 0xE8:
            case 0xE9:
            case 0xEA:
                assignInstruction(instruction,opcode,LD,DATA_16,REG_A,1,8);
                break;
            case 0xEB:
            case 0xEC:
            case 0xED:
            case 0xEE:
            case 0xEF:
            case 0xF0:
                ssignInstruction(instruction,opcode,LDH,REG_A,DATA_8,1,8);
                break;
            case 0xF1:
            case 0xF2:
                assignInstruction(instruction,opcode,LD,REG_A,REG_C,1,8);
                break;
            case 0xF3:
            case 0xF4:
            case 0xF5:
            case 0xF6:
            case 0xF7:
            case 0xF8:
                assignInstruction(instruction,opcode,LDHL,STACK_POINTER,DATA_8,1,4);
                break;
            case 0xF9:
                assignInstruction(instruction,opcode,LD,STACK_POINTER,REG_HL,1,4);
                break;
            case 0xFA:
                assignInstruction(instruction,opcode,LD,REG_A,DATA_16,1,8);
                break;
            case 0xFB:
            case 0xFC:
            case 0xFD:
            case 0xFE:
            case 0xFF:
            default:
                instruction = NULL;
                break;
        }
    }
    return;
}
