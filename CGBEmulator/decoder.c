//
//  decoder.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "decoder.h"
#include "executor.h"

/*
static uint8_t *regs[8];

void decodeInstruction(uint8_t opcode, MainRegisters mainRegs) {
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
                    assignInstruction(instruction,opcode,ADD_A,REG_A,source,1,cycleDur);
                    break;
                case 1:
                    assignInstruction(instruction,opcode,ADC_A,REG_A,source,1,cycleDur);
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
            case 0x01:
                assignInstruction(instruction,opcode,LD,REG_BC,DATA_16,3,12);
                break;
            case 0x02:
                assignInstruction(instruction,opcode,LD,REG_BC,REG_A,1,8);
                break;
            case 0x03:
                assignInstruction(instruction,opcode,INC,REG_BC,REG_BC,1,8);
                break;
            case 0x04:
                assignInstruction(instruction,opcode,INC,REG_B,REG_B,1,4);
                break;
            case 0x05:
                assignInstruction(instruction,opcode,DEC,REG_B,REG_B,1,4);
                break;
            case 0x06: // LD 8 bit val
                assignInstruction(instruction,opcode,LD,REG_B,DATA_8,2,8);
                break;
            case 0x07:
                assignInstruction(instruction,opcode,RLCA,NOREG,NOREG,1,4);
                break;
            case 0x08:
                assignInstruction(instruction,opcode,LD,DATA_16,REG_SP,3,20);
                break;
            case 0x09:
                assignInstruction(instruction,opcode,ADD_A,REG_HL,REG_BC,1,8);
                break;
            case 0x0A:
                assignInstruction(instruction,opcode,LD,REG_A,REG_BC,1,8);
                break;
            case 0x0B:
                assignInstruction(instruction,opcode,DEC,REG_BC,REG_BC,1,8);
                break;
            case 0x0C:
                assignInstruction(instruction,opcode,INC,REG_C,REG_C,1,4);
                break;
            case 0x0D:
                assignInstruction(instruction,opcode,DEC,REG_C,REG_C,1,4);
                break;
            case 0x0E:
                assignInstruction(instruction,opcode,LD,REG_C,DATA_8,2,8);
                break;
            case 0x0F:
                assignInstruction(instruction,opcode,RRCA,NOREG,NOREG,1,4);
                break;
            case 0x10:
                assignInstruction(instruction,opcode,STOP,NOREG,NOREG,2,4);
                break;
            case 0x11:
                assignInstruction(instruction,opcode,LD,REG_DE,DATA_16,3,12);
                break;
            case 0x12:
                assignInstruction(instruction,opcode,LD,REG_DE,REG_A,1,8);
                break;
            case 0x13:
                assignInstruction(instruction,opcode,INC,REG_DE,REG_DE,1,8);
                break;
            case 0x14:
                assignInstruction(instruction,opcode,INC,REG_D,REG_D,1,4);
                break;
            case 0x15:
                assignInstruction(instruction,opcode,DEC,REG_D,REG_D,1,4);
                break;
            case 0x16:
                assignInstruction(instruction,opcode,LD,REG_D,DATA_8,2,8);
                break;
            case 0x17:
                assignInstruction(instruction,opcode,RLA,NOREG,NOREG,1,4);
                break;
            case 0x18:
                assignInstruction(instruction,opcode,JR,NOREG,DATA_8,2,12);
                break;
            case 0x19:
                assignInstruction(instruction,opcode,ADD_A,REG_HL,REG_DE,1,8);
                break;
            case 0x1A:
                assignInstruction(instruction,opcode,LD,REG_A,REG_DE,1,8);
                break;
            case 0x1B:
                assignInstruction(instruction,opcode,DEC,REG_DE,REG_DE,1,8);
                break;
            case 0x1C:
                assignInstruction(instruction,opcode,INC,REG_E,REG_E,1,4);
                break;
            case 0x1D:
                assignInstruction(instruction,opcode,DEC,REG_E,REG_E,1,4);
                break;
            case 0x1E:
                assignInstruction(instruction,opcode,LD,REG_E,DATA_8,2,8);
                break;
            case 0x1F:
                assignInstruction(instruction,opcode,RRA,NOREG,NOREG,1,4);
                break;
            case 0x20:
                assignInstruction(instruction,opcode,JR,NOREG,DATA_8,2,12);
                break;
            case 0x21:
                assignInstruction(instruction,opcode,LD,REG_HL,DATA_16,3,12);
                break;
            case 0x22:
                assignInstruction(instruction,opcode,LDI,REG_HL,REG_A,1,8);
                break;
            case 0x23:
                assignInstruction(instruction,opcode,INC,REG_HL,REG_HL,1,8);
                break;
            case 0x24:
                assignInstruction(instruction,opcode,INC,REG_H,REG_H,1,4);
                break;
            case 0x25:
                assignInstruction(instruction,opcode,DEC,REG_H,REG_H,1,4);
                break;
            case 0x26:
                assignInstruction(instruction,opcode,LD,REG_H,DATA_8,2,8);
                break;
            case 0x27:
                assignInstruction(instruction,opcode,DAA,NOREG,NOREG,1,4);
                break;
            case 0x28:
                assignInstruction(instruction,opcode,JR,NOREG,DATA_8,2,12);
                break;
            case 0x29:
                assignInstruction(instruction,opcode,ADD_A,REG_HL,REG_HL,1,8);
                break;
            case 0x2A:
                assignInstruction(instruction,opcode,LDI,REG_A,REG_HL,1,8);
                break;
            case 0x2B:
                assignInstruction(instruction,opcode,DEC,REG_HL,REG_HL,1,8);
                break;
            case 0x2C:
                assignInstruction(instruction,opcode,INC,REG_L,REG_L,1,4);
                break;
            case 0x2D:
                assignInstruction(instruction,opcode,DEC,REG_L,REG_L,1,4);
                break;
            case 0x2E:
                assignInstruction(instruction,opcode,LD,REG_L,DATA_8,2,8);
                break;
            case 0x2F:
                assignInstruction(instruction,opcode,CPL,NOREG,NOREG,1,4);
                break;
            case 0x30:
                assignInstruction(instruction,opcode,JR,NOREG,DATA_8,2,12);
                break;
            case 0x31:
                assignInstruction(instruction,opcode,LD,REG_SP,DATA_16,3,12);
                break;
            case 0x32:
                assignInstruction(instruction,opcode,LDD,REG_HL,REG_A,1,8);
                break;
            case 0x33:
                assignInstruction(instruction,opcode,INC,REG_SP,REG_SP,1,8);
                break;
            case 0x34:
                assignInstruction(instruction,opcode,INC,REG_HL,REG_HL,1,12);
                break;
            case 0x35:
                assignInstruction(instruction,opcode,DEC,REG_HL,REG_HL,1,12);
                break;
            case 0x36:
                assignInstruction(instruction,opcode,LD,REG_HL,DATA_8,2,12);
                break;
            case 0x37:
                assignInstruction(instruction,opcode,SCF,NOREG,NOREG,1,4);
                break;
            case 0x38:
                assignInstruction(instruction,opcode,JR,NOREG,DATA_8,2,12);
                break;
            case 0x39:
                assignInstruction(instruction,opcode,ADD_A,REG_HL,REG_SP,1,8);
                break;
            case 0x3A:
                assignInstruction(instruction,opcode,LDD,REG_A,REG_HL,1,8);
                break;
            case 0x3B:
                assignInstruction(instruction,opcode,DEC,REG_SP,REG_SP,1,8);
                break;
            case 0x3C:
                assignInstruction(instruction,opcode,INC,REG_A,REG_A,1,4);
                break;
            case 0x3D:
                assignInstruction(instruction,opcode,DEC,REG_A,REG_A,1,4);
                break;
            case 0x3E:
                assignInstruction(instruction,opcode,LD,REG_A,DATA_8,2,8);
                break;
            case 0x3F:
                assignInstruction(instruction,opcode,CCF,NOREG,NOREG,1,4);
                break;
            case 0x76: // HALT
                assignInstruction(instruction,opcode,HALT,NOREG,NOREG,1,4);
                break;
            case 0xC0:
                assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
                break;
            case 0xC1:
                assignInstruction(instruction,opcode,POP,REG_SP,REG_BC,1,12);
                break;
            case 0xC2:
                assignInstruction(instruction,opcode,JP,NOREG,DATA_16,3,16);
                break;
            case 0xC3:
                assignInstruction(instruction,opcode,JP,NOREG,DATA_16,3,16);
                break;
            case 0xC4:
                assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
                break;
            case 0xC5:
                assignInstruction(instruction,opcode,PUSH,REG_SP,REG_BC,1,16);
                break;
            case 0xC6:
                assignInstruction(instruction,opcode,ADD_A,REG_A,DATA_8,2,8);
                break;
            case 0xC7:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xC8:
                assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
                break;
            case 0xC9:
                assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,16);
                break;
            case 0xCA:
                assignInstruction(instruction,opcode,JP,NOREG,DATA_16,3,16);
                break;
            case 0xCB: // Prefix used fo CB table
                break;
            case 0xCC:
                assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
                break;
            case 0xCD:
                assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
                break;
            case 0xCE:
                assignInstruction(instruction,opcode,ADC_A,REG_A,DATA_8,2,8);
                break;
            case 0xCF:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xD0:
                assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
                break;
            case 0xD1:
                assignInstruction(instruction,opcode,POP,REG_SP,REG_DE,1,12);
                break;
            case 0xD2:
                assignInstruction(instruction,opcode,JP,NOREG,DATA_16,3,16);
                break;
            case 0xD3: // NOT USED
                instruction = NULL;
                break;
            case 0xD4:
                assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
                break;
            case 0xD5:
                assignInstruction(instruction,opcode,PUSH,REG_SP,REG_DE,1,16);
                break;
            case 0xD6:
                assignInstruction(instruction,opcode,SUB,REG_A,DATA_8,2,8);
                break;
            case 0xD7:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xD8:
                assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
                break;
            case 0xD9:
                assignInstruction(instruction,opcode,RETI,NOREG,NOREG,1,16);
                break;
            case 0xDA:
                assignInstruction(instruction,opcode,JP,NOREG,DATA_16,1,16);
                break;
            case 0xDB: // NOT USED
                instruction = NULL;
                break;
            case 0xDC:
                assignInstruction(instruction,opcode,CALL,REG_C,DATA_16,3,24);
                break;
            case 0xDD: // NOT USED
                instruction = NULL;
                break;
            case 0xDE:
                assignInstruction(instruction,opcode,SBC_A,REG_A,DATA_8,2,8);
                break;
            case 0xDF:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xE0:
                assignInstruction(instruction,opcode,LDH,DATA_8,REG_A,2,12);
                break;
            case 0xE1:
                assignInstruction(instruction,opcode,POP,REG_SP,REG_HL,1,12);
                break;
            case 0xE2:
                assignInstruction(instruction,opcode,LD,REG_C,REG_A,2,8);
                break;
            case 0xE3: // NOT USED
                instruction = NULL;
                break;
            case 0xE4: // NOT USED
                instruction = NULL;
                break;
            case 0xE5:
                assignInstruction(instruction,opcode,PUSH,REG_SP,REG_HL,1,16);
                break;
            case 0xE6:
                assignInstruction(instruction,opcode,AND,REG_A,DATA_8,2,8);
                break;
            case 0xE7:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xE8:
                assignInstruction(instruction,opcode,ADD_A,REG_SP,DATA_8,2,16);
                break;
            case 0xE9:
                assignInstruction(instruction,opcode,JP,NOREG,REG_HL,1,4);
                break;
            case 0xEA:
                assignInstruction(instruction,opcode,LD,DATA_16,REG_A,3,16);
                break;
            case 0xEB: // NOT USED
                instruction = NULL;
                break;
            case 0xEC: // NOT USED
                instruction = NULL;
                break;
            case 0xED: // NOT USED
                instruction = NULL;
                break;
            case 0xEE:
                assignInstruction(instruction,opcode,XOR,REG_A,DATA_8,2,8);
                break;
            case 0xEF:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xF0:
                assignInstruction(instruction,opcode,LDH,REG_A,DATA_8,2,12);
                break;
            case 0xF1:
                assignInstruction(instruction,opcode,POP,REG_SP,REG_AF,1,12);
                break;
            case 0xF2:
                assignInstruction(instruction,opcode,LD,REG_A,REG_C,2,8);
                break;
            case 0xF3:
                assignInstruction(instruction,opcode,DI,NOREG,NOREG,1,4);
                break;
            case 0xF4: // NOT USED
                instruction = NULL;
                break;
            case 0xF5:
                assignInstruction(instruction,opcode,PUSH,REG_SP,REG_AF,1,16);
                break;
            case 0xF6:
                assignInstruction(instruction,opcode,OR,REG_A,DATA_8,2,8);
                break;
            case 0xF7:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            case 0xF8:
                assignInstruction(instruction,opcode,LDHL,REG_SP,DATA_8,2,16);
                break;
            case 0xF9:
                assignInstruction(instruction,opcode,LD,REG_SP,REG_HL,1,4);
                break;
            case 0xFA:
                assignInstruction(instruction,opcode,LD,REG_A,DATA_16,3,16);
                break;
            case 0xFB:
                assignInstruction(instruction,opcode,EI,NOREG,NOREG,1,4);
                break;
            case 0xFC:
                // NOT USED
                instruction = NULL;
                break;
            case 0xFD:
                // NOT USED
                instruction = NULL;
                break;
            case 0xFE:
                assignInstruction(instruction,opcode,CP,REG_A,DATA_8,2,8);
                break;
            case 0xFF:
                assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
                break;
            default:
                instruction = NULL;
                break;
        }
    }
    return;
}*/
