//
//  constants.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/23/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef constants_h
#define constants_h

#include <stdint.h>

typedef uint8_t byte;
typedef int8_t signed_byte;
typedef uint16_t word;

#define NUMREGS 8
#define LOWERBITS (0x0F)
#define SCREENSIZE 256
#define PIXELWIDTH 5

#define ZeroFlag(flags) ({*flags & BIT7;})
#define SubtractionFlag(flags) ({*flags & BIT6;})
#define HalfCarryFlag(flags) ({*flags & BIT5;})
#define CarryFlag(flags) ({*flags & BIT4;})

#define RegisterPair(reg1,reg2) ({ (word) ( (((word)reg1) << 8) | ((word)reg2)) ;})

#define BIT7 0x80
#define BIT6 0x40
#define BIT5 0x20
#define BIT4 0x10
#define BIT3 0x08
#define BIT2 0x04
#define BIT1 0x02
#define BIT0 0x01

enum ALUTYPE {
    ADD_T,
    ADC_T,
    SUB_T,
    SBC_T,
    AND_T,
    XOR_T,
    OR_T,
    CP_T
};

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

struct LCD_TILE {
    byte tile_data[16];
};
#endif /* constants_h */