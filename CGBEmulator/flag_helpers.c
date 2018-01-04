//
//  flag_helpers.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/3/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include "flag_helpers.h"
#include "constants.h"

void setADDZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags){
    if (reg_1 == 0 && reg_2 == 0)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
}

void setSUBZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags){
    if (reg_1 == reg_2)
        setZeroFlag(flags);
    else
        clearZeroFlag(flags);
}

void setADD8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0F) + (reg_2 & 0x0F) > 0x0F)
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setSUB8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0F) < (reg_2 & 0x0F))
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setADD16BitHalfCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags) {
    if((reg_1 & 0x0FFF) + (reg_2 & 0x0FFF) > 0x0FFF)
        setHalfCarryFlag(flags);
    else
        clearHalfCarryFlag(flags);
}

void setADD8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    uint8_t sum = reg_1 + reg_2;
    if(sum < reg_1 && sum < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}

void setSUB8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags) {
    if(reg_1 < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}

void setADD16BitCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags) {
    uint16_t sum = reg_1 + reg_2;
    if(sum < reg_1 && sum < reg_2)
        setCarryFlag(flags);
    else
        clearCarryFlag(flags);
}
