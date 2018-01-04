//
//  flag_helpers.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/3/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include "flag_helpers.h"
#include "constants.h"

#define setZeroFlag(flags) ({*flags = *flags | BIT7;})
#define setHalfCarryFlag(flags) ({*flags = *flags | BIT5;})
#define setCarryFlag(flags) ({*flags = *flags | BIT4;})

#define clearZeroFlag(flags) ({*flags = *flags & ~BIT7;})
#define clearHalfCarryFlag(flags) ({*flags = *flags & ~BIT5;})
#define clearCarryFlag(flags) ({*flags = *flags & ~BIT4;})

void setArithmeticZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags){
    if (reg_1 == 0 && reg_2 == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
}

void setCompareZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags){
    if (reg_1 == reg_2)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
}

void setArithmetic8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0F) + (reg_2 & 0x0F) > 0x0F)
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setCompare8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0F) < (reg_2 & 0x0F))
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setArithmetic16BitHalfCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0FFF) + (reg_2 & 0x0FFF) > 0x0FFF)
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setArithmetic8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    uint8_t sum = reg_1 + reg_2;
    if(sum < reg_1 && sum < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}

void setCompare8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if(reg_1 < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}

void setArithmetic16BitCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags) {
    uint16_t sum = reg_1 + reg_2;
    if(sum < reg_1 && sum < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}
