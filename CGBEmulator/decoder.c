//
//  decoder.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "decoder.h"
#include "executor.h"

extern byte isStopped;
extern byte isHalted;
extern byte intEnabled;
extern word cycles;


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
                // Do nothing
                cycles += 4;
                break;
            case 0x01:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                load_RegisterPair_With16BitData(&(mainRegs->reg_B),&(mainRegs->reg_C),data_word);
                cycles += 12;
                break;
            case 0x02:
                writeByte(RegisterPair(mainRegs->reg_B, mainRegs->reg_C), mainRegs->reg_A, mainMemory);
                cycles += 8;
                break;
            case 0x03:
                increment_RegisterPair(&(mainRegs->reg_B),&(mainRegs->reg_C));
				cycles += 8;
                break;
            case 0x04:
                increment_Register(&(mainRegs->reg_B));
				cycles += 4;
                break;
            case 0x05:
                decrement_Register(&(mainRegs->reg_B));
				cycles += 4;
                break;
            case 0x06: // LD 8 bit val
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_B),data_byte);
				cycles += 8;
                break;
            case 0x07:
                RLC(&(mainRegs->reg_A),&(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x08:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                writeWord(data_word,(mainRegs->stackPointer), mainMemory);
				cycles += 20;
                break;
            case 0x09:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_B), &(mainRegs->reg_C), &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0x0A:
                data_byte = readByteWithRegs(&(mainRegs->reg_B), &(mainRegs->reg_C), mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
				cycles += 8;
                break;
            case 0x0B:
                decrement_RegisterPair(&(mainRegs->reg_B),&(mainRegs->reg_C));
				cycles += 8;
                break;
            case 0x0C:
                increment_Register(&(mainRegs->reg_C));
				cycles += 4;
                break;
            case 0x0D:
                decrement_Register(&(mainRegs->reg_C));
				cycles += 4;
                break;
            case 0x0E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_C),data_byte);
				cycles += 8;
                break;
            case 0x0F:
                RRC(&(mainRegs->reg_A), &(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x10:
                isStopped = 1;
				cycles += 4;
                break;
            case 0x11:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                load_RegisterPair_With16BitData(&(mainRegs->reg_D), &(mainRegs->reg_E), data_word);
				cycles += 12;
                break;
            case 0x12:
                writeByte(RegisterPair(mainRegs->reg_D, mainRegs->reg_E), mainRegs->reg_A, mainMemory);
				cycles += 8;
                break;
            case 0x13:
                increment_RegisterPair(&(mainRegs->reg_D),&(mainRegs->reg_E));
				cycles += 8;
                break;
            case 0x14:
                increment_Register(&(mainRegs->reg_D));
				cycles += 4;
                break;
            case 0x15:
                decrement_Register(&(mainRegs->reg_D));
				cycles += 4;
                break;
            case 0x16:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_D),data_byte);
				cycles += 8;
                break;
            case 0x17:
                RL(&(mainRegs->reg_A), &(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x18:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				cycles += 8;
                break;
            case 0x19:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_D), &(mainRegs->reg_E), &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0x1A:
                data_byte = readByteWithRegs(&(mainRegs->reg_D), &(mainRegs->reg_E), mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
				cycles += 8;
                break;
            case 0x1B:
                decrement_RegisterPair(&(mainRegs->reg_D),&(mainRegs->reg_E));
				cycles += 8;
                break;
            case 0x1C:
                increment_Register(&(mainRegs->reg_E));
				cycles += 4;
                break;
            case 0x1D:
                decrement_Register(&(mainRegs->reg_E));
				cycles += 4;
                break;
            case 0x1E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_E),data_byte);
				cycles += 8;
                break;
            case 0x1F:
                RR(&(mainRegs->reg_A), &(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x20:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				cycles += 12;
                break;
            case 0x21:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                load_RegisterPair_With16BitData(&(mainRegs->reg_H), &(mainRegs->reg_L), data_word);
				cycles += 12;
                break;
            case 0x22:
                writeByte(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), mainRegs->reg_A, mainMemory);
                increment_RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L));
                cycles += 8;
                break;
            case 0x23:
                increment_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				cycles += 8;
                break;
            case 0x24:
                increment_Register(&(mainRegs->reg_H));
				cycles += 4;
                break;
            case 0x25:
                decrement_Register(&(mainRegs->reg_H));
				cycles += 4;
                break;
            case 0x26:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_H),data_byte);
				cycles += 8;
                break;
            case 0x27:
                DAA(&(mainRegs->reg_A), &(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x28:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				cycles += 12;
                break;
            case 0x29:
                ADD_16BIT(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0x2A:
                data_byte = readByteWithAddress(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
                increment_RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L));
				cycles += 8;
                break;
            case 0x2B:
                decrement_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				cycles += 8;
                break;
            case 0x2C:
                increment_Register(&(mainRegs->reg_L));
				cycles += 4;
                break;
            case 0x2D:
                decrement_Register(&(mainRegs->reg_L));
				cycles += 4;
                break;
            case 0x2E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_L),data_byte);
				cycles += 8;
                break;
            case 0x2F:
                complementA(&(mainRegs->reg_A));
				cycles += 4;
                break;
            case 0x30:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				cycles += 12;
                break;
            case 0x31:
                data_word = fetchWord(&(mainRegs->programCounter), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter) , data_word);
				cycles += 12;
                break;
            case 0x32:
                writeByte(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), mainRegs->reg_A, mainMemory);
                decrement_RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L));
                cycles += 8;
                break;
            case 0x33:
                increment_16BitRegister(&(mainRegs->stackPointer));
				cycles += 8;
                break;
            case 0x34:
                data_byte = readByteWithAddress(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), mainMemory);
                writeByte(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), data_byte+1, mainMemory);
				cycles += 12;
                break;
            case 0x35:
                decrement_RegisterPair(&(mainRegs->reg_H),&(mainRegs->reg_L));
				cycles += 12;
                break;
            case 0x36:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                writeByte(RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L)), data_byte, mainMemory);
				cycles += 12;
                break;
            case 0x37:
                SCF(&(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x38:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),mainRegs->programCounter + data_byte);
				cycles += 12;
                break;
            case 0x39:
                ADD_16BIT_data(&(mainRegs->reg_H), &(mainRegs->reg_L), mainRegs->stackPointer, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0x3A:
                data_byte = readByteWithAddress(RegisterPair(mainRegs->reg_H, mainRegs->reg_L), mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
                decrement_RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L));
				cycles += 8;
                break;
            case 0x3B:
                decrement_16BitRegister(&(mainRegs->stackPointer));
				cycles += 8;
                break;
            case 0x3C:
                increment_Register(&(mainRegs->reg_A));
				cycles += 4;
                break;
            case 0x3D:
                decrement_Register(&(mainRegs->reg_A));
				cycles += 4;
                break;
            case 0x3E:
                data_byte = fetchByte(&(mainRegs->programCounter),mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A),data_byte);
				cycles += 8;
                break;
            case 0x3F:
                CCF(&(mainRegs->reg_F));
				cycles += 4;
                break;
            case 0x76: // HALT
                isHalted = 1;
				cycles += 4;
                break;
            case 0xC0:
                if (ZeroFlag(&(mainRegs->reg_F)) == 0)
                    popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
				cycles += 20;
                break;
            case 0xC1:
                pop(&(mainRegs->reg_B), &(mainRegs->reg_C), &(mainRegs->stackPointer), mainMemory);
				cycles += 12;
                break;
            case 0xC2:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				cycles += 16;
                break;
            case 0xC3:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                jump_address(&(mainRegs->programCounter),data_word);
				cycles += 16;
                break;
            case 0xC4:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if (ZeroFlag(&(mainRegs->reg_F)) == 0) {
                    push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                    load_16BitRegister_With16BitData(&(mainRegs->programCounter), data_word);
                }
				cycles += 12;
                break;
            case 0xC5:
                push(&(mainRegs->reg_B), &(mainRegs->reg_C), &(mainRegs->stackPointer), mainMemory);
				cycles += 16;
                break;
            case 0xC6:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                ADD_8BIT(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xC7:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0));
				cycles += 16;
                break;
            case 0xC8:
                if (ZeroFlag(&(mainRegs->reg_F)) != 0)
                    popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
				cycles += 20;
                break;
            case 0xC9:
                popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
				cycles += 16;
                break;
            case 0xCA:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(ZeroFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				cycles += 16;
                break;
            case 0xCB: // Prefix used fo CB table
                break;
            case 0xCC:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if (ZeroFlag(&(mainRegs->reg_F)) != 0) {
                    push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                    load_16BitRegister_With16BitData(&(mainRegs->programCounter), data_word);
                }
				cycles += 4;
                break;
            case 0xCD:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), data_word);
				cycles += 12;
                break;
            case 0xCE:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                ADC(&(mainRegs->reg_A), &(data_byte), &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xCF:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x08));
				cycles += 16;
                break;
            case 0xD0:
                if (CarryFlag(&(mainRegs->reg_F)) == 0)
                    popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
				cycles += 8;
                break;
            case 0xD1:
                pop(&(mainRegs->reg_D), &(mainRegs->reg_E), &(mainRegs->stackPointer), mainMemory);
				cycles += 12;
                break;
            case 0xD2:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) == 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				cycles += 16;
                break;
            case 0xD3: // NOT USED
                // Do not Execute
                break;
            case 0xD4:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if (CarryFlag(&(mainRegs->reg_F)) == 0) {
                    push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                    load_16BitRegister_With16BitData(&(mainRegs->programCounter), data_word);
                }
				cycles += 12;
                break;
            case 0xD5:
                push(&(mainRegs->reg_D), &(mainRegs->reg_E), &(mainRegs->stackPointer), mainMemory);
				cycles += 16;
                break;
            case 0xD6:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                SUB(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xD7:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x10));
				cycles += 16;
                break;
            case 0xD8:
                if (CarryFlag(&(mainRegs->reg_F)) != 0)
                    popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
				cycles += 8;
                break;
            case 0xD9:
                popWord(&(mainRegs->programCounter), &(mainRegs->stackPointer), mainMemory);
                intEnabled = 1;
				cycles += 16;
                break;
            case 0xDA:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if(CarryFlag(&(mainRegs->reg_F)) != 0)
                    jump_address(&(mainRegs->programCounter),data_word);
				cycles += 16;
                break;
            case 0xDB: // NOT USED
                // Do not Execute
                break;
            case 0xDC:
                data_word = fetchWord(&(mainRegs->programCounter),mainMemory);
                if (CarryFlag(&(mainRegs->reg_F)) != 0) {
                    push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                    load_16BitRegister_With16BitData(&(mainRegs->programCounter), data_word);
                }
				cycles += 12;
                break;
            case 0xDD: // NOT USED
                // Do not Execute
                break;
            case 0xDE:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                SBC(&(mainRegs->reg_A), &(data_byte), &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xDF:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x18));
				cycles += 16;
                break;
            case 0xE0:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                writeByte(0xFF00 + data_byte, mainRegs->reg_A, mainMemory);
				cycles += 12;
                break;
            case 0xE1:
                pop(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->stackPointer), mainMemory);
				cycles += 12;
                break;
            case 0xE2:
                writeByte((word)(mainRegs->reg_C), mainRegs->reg_A, mainMemory);
				cycles += 8;
                break;
            case 0xE3: // NOT USED
                // Do not Execute
                break;
            case 0xE4: // NOT USED
                // Do not Execute
                break;
            case 0xE5:
                push(&(mainRegs->reg_H), &(mainRegs->reg_L), &(mainRegs->stackPointer), mainMemory);
				cycles += 16;
                break;
            case 0xE6:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                AND(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xE7:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x20));
				cycles += 16;
                break;
            case 0xE8:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                ADD_SP(&(mainRegs->stackPointer), (signed_byte)data_byte, &(mainRegs->reg_F));
				cycles += 16;
                break;
            case 0xE9:
                data_word = ((word)mainRegs->reg_H) << 8;
                data_word = data_word & ((word)mainRegs->reg_L);
                jump_address(&(mainRegs->programCounter),data_word);
				cycles += 4;
                break;
            case 0xEA:
                data_word = fetchWord(&(mainRegs->programCounter), mainMemory);
                writeByte(data_word, mainRegs->reg_A, mainMemory);
				cycles += 16;
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
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                XOR(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xEF:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x28));
				cycles += 16;
                break;
            case 0xF0:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                data_byte = readByteWithAddress(data_byte + 0xFF00, mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
				cycles += 12;
                break;
            case 0xF1:
                pop(&(mainRegs->reg_A), &(mainRegs->reg_F), &(mainRegs->stackPointer), mainMemory);
				cycles += 12;
                break;
            case 0xF2:
                data_byte = readByteWithAddress((word)(mainRegs->reg_C), mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
				cycles += 8;
                break;
            case 0xF3:
                intEnabled = 0;
				cycles += 4;
                break;
            case 0xF4: // NOT USED
                // Do not Execute
                break;
            case 0xF5:
                push(&(mainRegs->reg_A), &(mainRegs->reg_F), &(mainRegs->stackPointer), mainMemory);
				cycles += 16;
                break;
            case 0xF6:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                OR(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xF7:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x30));
				cycles += 16;
                break;
            case 0xF8:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                load_RegisterPair_With16BitData(&(mainRegs->reg_H), &(mainRegs->reg_L), mainRegs->stackPointer + data_byte);
				cycles += 16;
                break;
            case 0xF9:
                load_16BitRegister_With16BitData(&(mainRegs->stackPointer), RegisterPair(&(mainRegs->reg_H), &(mainRegs->reg_L)));
				cycles += 4;
                break;
            case 0xFA:
                data_word = fetchWord(&(mainRegs->programCounter), mainMemory);
                data_byte = readByteWithAddress(data_word, mainMemory);
                load_8BitRegister_With8BitData(&(mainRegs->reg_A), data_byte);
				cycles += 16;
                break;
            case 0xFB:
                intEnabled = 1;
				cycles += 4;
                break;
            case 0xFC: // NOT USED
                // Do not Execute
                break;
            case 0xFD: // NOT USED
                // Do not Execute
                break;
            case 0xFE:
                data_byte = fetchByte(&(mainRegs->programCounter), mainMemory);
                CP(&(mainRegs->reg_A), &data_byte, &(mainRegs->reg_F));
				cycles += 8;
                break;
            case 0xFF:
                push_16bit_address(mainRegs->programCounter, &(mainRegs->stackPointer), mainMemory);
                load_16BitRegister_With16BitData(&(mainRegs->programCounter), (word)(0x38));
				cycles += 16;
                break;
            default:
                // Do not Execute
                break;
        }
    }

}
