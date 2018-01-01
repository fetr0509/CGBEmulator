//
//  debug_strings.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include "debug_strings.h"
#include "constants.h"

char* getRegisterTypeDebugString(enum REGISTERTYPE regType) {
    switch (regType) {
        case REG_B:
            return "REG_B";
        case REG_C:
            return "REG_C";
        case REG_D:
            return "REG_D";
        case REG_E:
            return "REG_E";
        case REG_H:
            return "REG_H";
        case REG_L:
            return "REG_L";
        case REG_ADDR_HL:
            return "REG_ADDR_HL";
        case REG_A:
            return "REG_A";
        case REG_BC:
            return "REG_BC";
        case REG_DE:
            return "REG_DE";
        case REG_HL:
            return "REG_HL";
        case REG_SP:
            return "REG_SP";
        case REG_AF:
            return "REG_AF";
        case NOREG:
            return "NOREG";
        case DATA_8:
            return "DATA_8";
        case DATA_16:
            return "DATA_16";
        default:
            return "ERROR: UNKNOWN REG TYPE";
    }
};

char* getConditionalsDebugString(enum CONDITIONALS conditionalType) {
    switch (conditionalType) {
        case NZ:
            return "NZ";
        case Z:
            return "Z";
        case NC:
            return "NC";
        case C:
            return "C";
        case PO:
            return "PO";
        case PE:
            return "PE";
        case P:
            return "P";
        case M:
            return "M";
        default:
            return "ERROR: UNKNOWN CONDITIONAL TYPE";
    }
}

char* getOpcodeDebugString(enum OPCODE_TYPE opcodeType) {
    switch (opcodeType) {
        case NOP:
            return "NOP";
        case LD:
            return "LD";
        case LDD:
            return "LDD";
        case LDI:
            return "LDI";
        case LDH:
            return "LDH";
        case LDHL:
            return "LDHL";
        case PUSH:
            return "PUSH";
        case POP:
            return "POP";
        case ADD_A:
            return "ADD_A";
        case ADC_A:
            return "ADC_A";
        case SUB:
            return "SUB";
        case SUBC:
            return "SUBC";
        case SBC_A:
            return "SBC_A";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case XOR:
            return "XOR";
        case CP:
            return "CP";
        case INC:
            return "INC";
        case DEC:
            return "DEC";
        case SWAP:
            return "SWAP";
        case DAA:
            return "DAA";
        case CPL:
            return "CPL";
        case CCF:
            return "CCF";
        case SCF:
            return "SCF";
        case HALT:
            return "HALT";
        case STOP:
            return "STOP";
        case DI:
            return "DI";
        case EI:
            return "EI";
        case RLCA:
            return "RLCA";
        case RLA:
            return "RLA";
        case RRCA:
            return "RRCA";
        case RRA:
            return "RRA";
        case RLC:
            return "RLC";
        case RL:
            return "RL";
        case RRC:
            return "RRC";
        case RR:
            return "RR";
        case SLL:
            return "SLL";
        case SLA:
            return "SLA";
        case SRL:
            return "SRL";
        case SRA:
            return "SRA";
        case BIT:
            return "BIT";
        case SET:
            return "SET";
        case RES:
            return "RES";
        case JP:
            return "JP";
        case JR:
            return "JR";
        case CALL:
            return "CALL";
        case RST:
            return "RST";
        case RET:
            return "RET";
        case RETI:
            return "RETI";
        default:
            return "ERROR: UNKNOWN OPCODE";
    }
}
