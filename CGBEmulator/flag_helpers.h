//
//  flag_helpers.h
//  CGBEmulator
//
//  Created by Peter Fetros on 1/3/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#ifndef flag_helpers_h
#define flag_helpers_h

#include <stdio.h>

#define setSubtractionFlag(flags) ({*flags = *flags | BIT6;})
#define clearSubtractionFlag(flags) ({*flags = *flags & ~BIT6;})

void setArithmeticZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setCompareZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);

void setArithmetic8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setCompare8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setArithmetic16BitHalfCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags);

void setArithmetic8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setCompare8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setArithmetic16BitCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags);

#endif /* flag_helpers_h */
