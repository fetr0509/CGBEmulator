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

#define zeroFlag(flagReg) ((flagReg >> 7) & 1)
#define subtractFlag(flagReg) ((flagReg >> 6) & 1)
#define halfCarryFlag(flagReg) ((flagReg >> 5) & 1)
#define carryFlag(flagReg) ((flagReg >> 4) & 1)

#define LOWERBITS (0x0F)


typedef struct mainRegisters {
    uint8_t reg_A;
    uint8_t reg_F;
    
    uint8_t reg_B;
    uint8_t reg_C;
    
    uint8_t reg_D;
    uint8_t reg_E;
    
    uint8_t reg_H;
    uint8_t reg_L;
    
    uint16_t programCounter;
    uint16_t stackPointer;
} mainRegisters;

void setRegA(mainRegisters regs, uint8_t value);
void setRegF(mainRegisters regs, uint8_t value);
void setRegB(mainRegisters regs, uint8_t value);
void setRegC(mainRegisters regs, uint8_t value);
void setRegD(mainRegisters regs, uint8_t value);
void setRegE(mainRegisters regs, uint8_t value);
void setRegH(mainRegisters regs, uint8_t value);
void setRegL(mainRegisters regs, uint8_t value);

void setRegAF(mainRegisters regs, uint16_t value);
void setRegBC(mainRegisters regs, uint16_t value);
void setRegDE(mainRegisters regs, uint16_t value);
void setRegHL(mainRegisters regs, uint16_t value);

#endif /* main_registers_h */
