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

#define setZeroFlag(flags) ({*flags = *flags | BIT7;})
#define setSubtractionFlag(flags) ({*flags = *flags | BIT6;})
#define setHalfCarryFlag(flags) ({*flags = *flags | BIT5;})
#define setCarryFlag(flags) ({*flags = *flags | BIT4;})

#define clearZeroFlag(flags) ({*flags = *flags & ~BIT7;})
#define clearSubtractionFlag(flags) ({*flags = *flags & ~BIT6;})
#define clearHalfCarryFlag(flags) ({*flags = *flags & ~BIT5;})
#define clearCarryFlag(flags) ({*flags = *flags & ~BIT4;})

void setADDZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setSUBZeroFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);

void setADD8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setSUB8BitHalfCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setADD16BitHalfCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags);

void setADD8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setSUB8BitCarryFlag(uint8_t reg_1, uint8_t reg_2, uint8_t *flags);
void setADD16BitCarryFlag(uint16_t reg_1, uint16_t reg_2, uint8_t *flags);

#endif /* flag_helpers_h */
