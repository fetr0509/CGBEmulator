//
//  constants.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/23/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef constants_h
#define constants_h

#define NUMREGS 8

enum REGISTERTYPE {
    REG_B,
    REG_C,
    REG_D,
    REG_E,
    REG_H,
    REG_L,
    REG_ADDR_HL,
    REG_A,
    REG_BC,
    REG_DE,
    REG_HL,
    REG_SP,
    REG_AF,
    NOREG,
    DATA_8,
    DATA_16
};

enum CONDITIONALS {
    NZ,
    Z,
    NC,
    C,
    PO,
    PE,
    P,
    M
};

enum OPCODE_TYPE {
    NOP,    // no operation
    LD,     // load
    LDD,    // load and decrement
    LDI,    // load and increment
    LDH,
    LDHL,
    PUSH,   // push onto stack
    POP,    // pop from stack
    ADD_A,  // add values
    ADC_A,  // add values and set carry flag
    SUB,    // subtract values
    SUBC,   // subtract values and set carry flag,
    SBC_A,  // subtract n + carry flag from register A
    AND,    // logical AND values
    OR,     // logical OR values
    XOR,    // logical XOR values
    CP,     // compare values
    INC,    // increment register
    DEC,    // decrement register
    SWAP,   // swap nibbles of register
    DAA,    // decimal adjust register A
    CPL,    // complement register A
    CCF,    // compliment carry flag (invert it)
    SCF,    // set carry flag
    HALT,   // power down CPU until inturrupt
    STOP,   // pwer down CPU and turn off screen
    DI,     // disable interupts
    EI,     // enable interupts
    RLCA,   // rotate register A left, bit 7 goes to carry
    RLA,    // rotate register A left, no carry
    RRCA,   // rotate register A right, bit 7 goes to carry
    RRA,    // rotate register A right, no carry
    RLC,    // rotate register left, bit 7 goes to carry
    RL,     // rotate register left, no carry
    RRC,    // rotate register right, bit 7 goes to carry
    RR,     // rotate register right, no carry
    SLL,
    SLA,    // left arithmetic shift
    SRL,    // right logical shift
    SRA,    // right arithmetic shift
    BIT,    // check bit and set Z flag
    SET,    // set bit in register
    RES,    // reset bit in register
    JP,     // jump to register
    JR,     // jump to current address plus offset
    CALL,   // push next next address, then jump
    RST,    // push current address then jump to 0x0 + n
    RET,    // pop 2 bytes and jump to that address
    RETI,   // return but then enable inturrupts
};

#endif /* constants_h */