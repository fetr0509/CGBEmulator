//
//  decoder.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "decoder.h"
#include "executor.h"

void decodeInstruction(byte opcode, MainRegisters *mainRegs, MainMemory *mainMemory) {
    static byte data_byte = 0;
    static word data_word = 0;

    if (opcode >= 0x40 && opcode < 0x80 && opcode != 0x76) {
        byte lowNibble = opcode & LOWERBITS;

        void *source = &mainRegs;
        void *destination = &mainRegs;

        if (lowNibble % 8 == 6)
            printf("load HL\t");
        else
            source = ((byte*) source + (sizeof(byte) * (lowNibble%8)));

        if ((opcode - 0x40)/8 == 7)
            printf("load HL\t");
        else
            destination = ((byte*) destination + (sizeof(byte) * ((opcode - 0x40)/8)));

        load_8BitRegister_WithRegister((byte*)destination, (byte*)source);
    }
    else if (opcode >= 0x80 && opcode < 0xC0 && opcode != 0x76) {
        byte lowNibble = opcode & LOWERBITS;
        void *source = &mainRegs;
        enum ALUTYPE arithmeticType = (opcode - 0x80) / 8;

        if (lowNibble%8 == 6)
            printf("load HL\t");
        else
            source = ((byte*) source + (sizeof(byte) * (lowNibble%8)));

        switch (arithmeticType) {
            case ADD_T:
                ADD_8BIT(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case ADC_T:
                ADC(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case SUB_T:
                SUB(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case SBC_T:
                SBC(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case AND_T:
                AND(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case XOR_T:
                XOR(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case OR_T:
                OR(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            case CP_T:
                CP(&mainRegs->reg_A, source, &mainRegs->reg_F);
                break;
            default:
                break;
        }
    }
    else {
        switch (opcode) {
            case 0x00: // NOP
                // Do literally nothing
                break;
            case 0x01:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->reg_B),&(mainRegs->reg_C),data_word);
                mainRegs->cycles += 12;
                break;
            case 0x02:
                data_byte = readByteWithRegs(&(mainRegs->reg_B),&(mainRegs->reg_C),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A),data_byte);
                mainRegs->cycles += 8;
                break;
            case 0x03:
                increment_RegisterPair(&(mainRegs->reg_B),&(mainRegs->reg_C));
				mainRegs->cycles += 8;
                break;
            case 0x04:
                increment_Register(&(mainRegs->reg_B));
				mainRegs->cycles += 4;
                break;
            case 0x05:
                decrement_Register(&(mainRegs->reg_B));
				mainRegs->cycles += 4;
                break;
            case 0x06: // LD 8 bit val
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_B),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x07:
                //assignInstruction(instruction,opcode,RLCA,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x08:
                //assignInstruction(instruction,opcode,LD,DATA_16,REG_SP,3,20);
				mainRegs->cycles += 20;
                break;
            case 0x09:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_B), &(mainRegs->reg_C), &(mainRegs->reg_F));
				mainRegs->cycles += 8;
                break;
            case 0x0A:
                //assignInstruction(instruction,opcode,LD,REG_A,REG_BC,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x0B:
                decrement_RegisterPair(&(mainRegs->reg_B),&(mainRegs->reg_C));
				mainRegs->cycles += 8;
                break;
            case 0x0C:
                increment_Register(&(mainRegs->reg_C));
				mainRegs->cycles += 4;
                break;
            case 0x0D:
                decrement_Register(&(mainRegs->reg_C));
				mainRegs->cycles += 4;
                break;
            case 0x0E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_C),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x0F:
                //assignInstruction(instruction,opcode,RRCA,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x10:
                //assignInstruction(instruction,opcode,STOP,NOREG,NOREG,2,4);
				mainRegs->cycles += 4;
                break;
            case 0x11:
                //assignInstruction(instruction,opcode,LD,REG_DE,DATA_16,3,12);
				mainRegs->cycles += 12;
                break;
            case 0x12:
                //assignInstruction(instruction,opcode,LD,REG_DE,REG_A,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x13:
                increment_RegisterPair(&(mainRegs->reg_D),&(mainRegs->reg_E));
				mainRegs->cycles += 8;
                break;
            case 0x14:
                increment_Register(&(mainRegs->reg_D));
				mainRegs->cycles += 4;
                break;
            case 0x15:
                decrement_Register(&(mainRegs->reg_D));
				mainRegs->cycles += 4;
                break;
            case 0x16:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_D),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x17:
                //assignInstruction(instruction,opcode,RLA,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x18:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x19:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_D), &(mainRegs->reg_E), &(mainRegs->reg_F));
				mainRegs->cycles += 8;
                break;
            case 0x1A:
                //assignInstruction(instruction,opcode,LD,REG_A,REG_DE,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x1B:
                decrement_RegisterPair(&(mainRegs->reg_D),&(mainRegs->reg_E));
				mainRegs->cycles += 8;
                break;
            case 0x1C:
                increment_Register(&(mainRegs->reg_E));
				mainRegs->cycles += 4;
                break;
            case 0x1D:
                decrement_Register(&(mainRegs->reg_E));
				mainRegs->cycles += 4;
                break;
            case 0x1E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_E),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x1F:
                //assignInstruction(instruction,opcode,RRA,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x20:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				mainRegs->cycles += 12;
                break;
            case 0x21:
                //assignInstruction(instruction,opcode,LD,REG_HL,DATA_16,3,12);
				mainRegs->cycles += 12;
                break;
            case 0x22:
                //assignInstruction(instruction,opcode,LDI,REG_HL,REG_A,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x23:
                increment_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				mainRegs->cycles += 8;
                break;
            case 0x24:
                increment_Register(&(mainRegs->reg_H));
				mainRegs->cycles += 4;
                break;
            case 0x25:
                decrement_Register(&(mainRegs->reg_H));
				mainRegs->cycles += 4;
                break;
            case 0x26:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_H),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x27:
                //assignInstruction(instruction,opcode,DAA,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x28:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				mainRegs->cycles += 12;
                break;
            case 0x29:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_F));
				mainRegs->cycles += 8;
                break;
            case 0x2A:
                //assignInstruction(instruction,opcode,LDI,REG_A,REG_HL,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x2B:
                decrement_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				mainRegs->cycles += 8;
                break;
            case 0x2C:
                increment_Register(&(mainRegs->reg_L));
				mainRegs->cycles += 4;
                break;
            case 0x2D:
                decrement_Register(&(mainRegs->reg_L));
				mainRegs->cycles += 4;
                break;
            case 0x2E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_L),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x2F:
                //assignInstruction(instruction,opcode,CPL,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x30:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				mainRegs->cycles += 12;
                break;
            case 0x31:
                //assignInstruction(instruction,opcode,LD,REG_SP,DATA_16,3,12);
				mainRegs->cycles += 12;
                break;
            case 0x32:
                //assignInstruction(instruction,opcode,LDD,REG_HL,REG_A,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x33:
                //assignInstruction(instruction,opcode,INC,REG_SP,REG_SP,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x34:
                //assignInstruction(instruction,opcode,INC,REG_HL,REG_HL,1,12);
				mainRegs->cycles += 12;
                break;
            case 0x35:
                decrement_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				mainRegs->cycles += 12;
                break;
            case 0x36:
                //assignInstruction(instruction,opcode,LD,REG_HL,DATA_8,2,12);
				mainRegs->cycles += 12;
                break;
            case 0x37:
                //assignInstruction(instruction,opcode,SCF,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x38:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				mainRegs->cycles += 12;
                break;
            case 0x39:
                ADD_16BIT_data(&(mainRegs->reg_H), &(mainRegs->reg_L), mainRegs->stackPointer, &(mainRegs->reg_F));
				mainRegs->cycles += 8;
                break;
            case 0x3A:
                //assignInstruction(instruction,opcode,LDD,REG_A,REG_HL,1,8);
				mainRegs->cycles += 8;
                break;
            case 0x3B:
                decrement_16BitRegister(&(mainRegs->stackPointer));
				mainRegs->cycles += 8;
                break;
            case 0x3C:
                increment_Register(&(mainRegs->reg_A));
				mainRegs->cycles += 4;
                break;
            case 0x3D:
                decrement_Register(&(mainRegs->reg_A));
				mainRegs->cycles += 4;
                break;
            case 0x3E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A),data_byte);
				mainRegs->cycles += 8;
                break;
            case 0x3F:
                //assignInstruction(instruction,opcode,CCF,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0x76: // HALT
                //assignInstruction(instruction,opcode,HALT,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0xC0:
                //assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);wa
				mainRegs->cycles += 20;
                break;
            case 0xC1:
                //assignInstruction(instruction,opcode,POP,REG_SP,REG_BC,1,12);
				mainRegs->cycles += 12;
                break;
            case 0xC2:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 16;
                break;
            case 0xC3:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 16;
                break;
            case 0xC4:
                //assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
				mainRegs->cycles += 24;
                break;
            case 0xC5:
                //assignInstruction(instruction,opcode,PUSH,REG_SP,REG_BC,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xC6:
                //assignInstruction(instruction,opcode,ADD_A,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xC7:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xC8:
                //assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
				mainRegs->cycles += 20;
                break;
            case 0xC9:
                //assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xCA:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 16;
                break;
            case 0xCB: // Prefix used fo CB table
                break;
            case 0xCC:
                //assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
				mainRegs->cycles += 4;
                break;
            case 0xCD:
                //assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
				mainRegs->cycles += 4;
                break;
            case 0xCE:
                //assignInstruction(instruction,opcode,ADC_A,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xCF:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xD0:
                //assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
				mainRegs->cycles += 20;
                break;
            case 0xD1:
                //assignInstruction(instruction,opcode,POP,REG_SP,REG_DE,1,12);
				mainRegs->cycles += 12;
                break;
            case 0xD2:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 16;
                break;
            case 0xD3: // NOT USED
                // Do not Execute
                break;
            case 0xD4:
                //assignInstruction(instruction,opcode,CALL,NOREG,DATA_16,3,24);
				mainRegs->cycles += 24;
                break;
            case 0xD5:
                //assignInstruction(instruction,opcode,PUSH,REG_SP,REG_DE,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xD6:
                //assignInstruction(instruction,opcode,SUB,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xD7:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xD8:
                //assignInstruction(instruction,opcode,RET,NOREG,NOREG,1,20);
				mainRegs->cycles += 20;
                break;
            case 0xD9:
                //assignInstruction(instruction,opcode,RETI,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xDA:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 16;
                break;
            case 0xDB: // NOT USED
                // Do not Execute
                break;
            case 0xDC:
                //assignInstruction(instruction,opcode,CALL,REG_C,DATA_16,3,24);
				mainRegs->cycles += 24;
                break;
            case 0xDD: // NOT USED
                // Do not Execute
                break;
            case 0xDE:
                //assignInstruction(instruction,opcode,SBC_A,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xDF:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xE0:
                //assignInstruction(instruction,opcode,LDH,DATA_8,REG_A,2,12);
				mainRegs->cycles += 12;
                break;
            case 0xE1:
                //assignInstruction(instruction,opcode,POP,REG_SP,REG_HL,1,12);
				mainRegs->cycles += 12;
                break;
            case 0xE2:
                //assignInstruction(instruction,opcode,LD,REG_C,REG_A,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xE3: // NOT USED
                // Do not Execute
                break;
            case 0xE4: // NOT USED
                // Do not Execute
                break;
            case 0xE5:
                //assignInstruction(instruction,opcode,PUSH,REG_SP,REG_HL,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xE6:
                //assignInstruction(instruction,opcode,AND,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xE7:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xE8:
                //assignInstruction(instruction,opcode,ADD_A,REG_SP,DATA_8,2,16);
				mainRegs->cycles += 16;
                break;
            case 0xE9:
                data_word = ((word)mainRegs->reg_H) << 8;
                data_word = data_word & ((word)mainRegs->reg_L);
                jump_address(&(mainRegs->programCounter),data_word);
				mainRegs->cycles += 4;
                break;
            case 0xEA:
                //assignInstruction(instruction,opcode,LD,DATA_16,REG_A,3,16);
				mainRegs->cycles += 16;
                break;
            case 0xEB: // NOT USED
                // Do not Execute
                break;
            case 0xEC: // NOT USED
                // Do not Execute
                break;
            case 0xED: // NOT USED
                // Do not Execute
                break;
            case 0xEE:
                //assignInstruction(instruction,opcode,XOR,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xEF:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xF0:
                //assignInstruction(instruction,opcode,LDH,REG_A,DATA_8,2,12);
				mainRegs->cycles += 12;
                break;
            case 0xF1:
                //assignInstruction(instruction,opcode,POP,REG_SP,REG_AF,1,12);
				mainRegs->cycles += 12;
                break;
            case 0xF2:
                //assignInstruction(instruction,opcode,LD,REG_A,REG_C,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xF3:
                //assignInstruction(instruction,opcode,DI,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0xF4: // NOT USED
                // Do not Execute
                break;
            case 0xF5:
                //assignInstruction(instruction,opcode,PUSH,REG_SP,REG_AF,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xF6:
                //assignInstruction(instruction,opcode,OR,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xF7:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            case 0xF8:
                //assignInstruction(instruction,opcode,LDHL,REG_SP,DATA_8,2,16);
				mainRegs->cycles += 16;
                break;
            case 0xF9:
                //assignInstruction(instruction,opcode,LD,REG_SP,REG_HL,1,4);
				mainRegs->cycles += 4;
                break;
            case 0xFA:
                //assignInstruction(instruction,opcode,LD,REG_A,DATA_16,3,16);
				mainRegs->cycles += 16;
                break;
            case 0xFB:
                //assignInstruction(instruction,opcode,EI,NOREG,NOREG,1,4);
				mainRegs->cycles += 4;
                break;
            case 0xFC: // NOT USED
                // Do not Execute
                break;
            case 0xFD: // NOT USED
                // Do not Execute
                break;
            case 0xFE:
                //assignInstruction(instruction,opcode,CP,REG_A,DATA_8,2,8);
				mainRegs->cycles += 8;
                break;
            case 0xFF:
                //assignInstruction(instruction,opcode,RST,NOREG,NOREG,1,16);
				mainRegs->cycles += 16;
                break;
            default:
                // Do not Execute
                break;
        }
    }

}
