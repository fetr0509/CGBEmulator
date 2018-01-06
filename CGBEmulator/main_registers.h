//
//  main_registers.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef main_registers_h
#define main_registers_h

#include <stdio.h>
#include "constants.h"

#define zeroFlag(flagReg) ((flagReg >> 7) & 1)
#define subtractFlag(flagReg) ((flagReg >> 6) & 1)
#define halfCarryFlag(flagReg) ((flagReg >> 5) & 1)
#define carryFlag(flagReg) ((flagReg >> 4) & 1)

#define LOWERBITS (0x0F)


typedef struct MainRegisters {
    
    byte reg_B;
    byte reg_C;
    
    byte reg_D;
    byte reg_E;
    
    byte reg_H;
    byte reg_L;
    
    byte reg_F;
    byte reg_A;
    
    word programCounter;
    word stackPointer;
    
    
} MainRegisters;

void setRegA(MainRegisters regs, byte value);
void setRegF(MainRegisters regs, byte value);
void setRegB(MainRegisters regs, byte value);
void setRegC(MainRegisters regs, byte value);
void setRegD(MainRegisters regs, byte value);
void setRegE(MainRegisters regs, byte value);
void setRegH(MainRegisters regs, byte value);
void setRegL(MainRegisters regs, byte value);

void setRegAF(MainRegisters regs, word value);
void setRegBC(MainRegisters regs, word value);
void setRegDE(MainRegisters regs, word value);
void setRegHL(MainRegisters regs, word value);

#endif /* main_registers_h */
