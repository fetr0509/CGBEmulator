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
#include "constants.h"

#define setZeroFlag(flags) ({*flags = *flags | BIT7;})
#define setSubtractionFlag(flags) ({*flags = *flags | BIT6;})
#define setHalfCarryFlag(flags) ({*flags = *flags | BIT5;})
#define setCarryFlag(flags) ({*flags = *flags | BIT4;})

#define clearZeroFlag(flags) ({*flags = *flags & ~BIT7;})
#define clearSubtractionFlag(flags) ({*flags = *flags & ~BIT6;})
#define clearHalfCarryFlag(flags) ({*flags = *flags & ~BIT5;})
#define clearCarryFlag(flags) ({*flags = *flags & ~BIT4;})

void setADDZeroFlag(byte reg_1, byte reg_2, byte *flags);
void setSUBZeroFlag(byte reg_1, byte reg_2, byte *flags);

void setADD8BitHalfCarryFlag(byte reg_1, byte reg_2, byte *flags);
void setSUB8BitHalfCarryFlag(byte reg_1, byte reg_2, byte *flags);
void setADD16BitHalfCarryFlag(word reg_1, word reg_2, byte *flags);

void setADD8BitCarryFlag(byte reg_1, byte reg_2, byte *flags);
void setSUB8BitCarryFlag(byte reg_1, byte reg_2, byte *flags);
void setADD16BitCarryFlag(word reg_1, word reg_2, byte *flags);

#endif /* flag_helpers_h */
