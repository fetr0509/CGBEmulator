//
//  main_registers.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "main_registers.h"

void setRegA(mainRegisters regs, uint8_t value) {regs.reg_A = value;}
void setRegF(mainRegisters regs, uint8_t value) {regs.reg_F = value;}
void setRegB(mainRegisters regs, uint8_t value) {regs.reg_B = value;}
void setRegC(mainRegisters regs, uint8_t value) {regs.reg_C = value;}
void setRegD(mainRegisters regs, uint8_t value) {regs.reg_D = value;}
void setRegE(mainRegisters regs, uint8_t value) {regs.reg_E = value;}
void setRegH(mainRegisters regs, uint8_t value) {regs.reg_H = value;}
void setRegL(mainRegisters regs, uint8_t value) {regs.reg_L = value;}

void setRegBC(mainRegisters regs, uint16_t value) {
    regs.reg_B = value >> 8;
    regs.reg_C = value & LOWERBITS;
}
void setRegDE(mainRegisters regs, uint16_t value) {
    regs.reg_D = value >> 8;
    regs.reg_E = value & LOWERBITS;
}
void setRegHL(mainRegisters regs, uint16_t value) {
    regs.reg_H = value >> 8;
    regs.reg_L = value & LOWERBITS;
}
