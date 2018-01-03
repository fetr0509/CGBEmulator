//
//  main_registers.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "main_registers.h"

void setRegA(MainRegisters regs, uint8_t value) {regs.reg_A = value;}
void setRegF(MainRegisters regs, uint8_t value) {regs.reg_F = value;}
void setRegB(MainRegisters regs, uint8_t value) {regs.reg_B = value;}
void setRegC(MainRegisters regs, uint8_t value) {regs.reg_C = value;}
void setRegD(MainRegisters regs, uint8_t value) {regs.reg_D = value;}
void setRegE(MainRegisters regs, uint8_t value) {regs.reg_E = value;}
void setRegH(MainRegisters regs, uint8_t value) {regs.reg_H = value;}
void setRegL(MainRegisters regs, uint8_t value) {regs.reg_L = value;}

void setRegBC(MainRegisters regs, uint16_t value) {
    regs.reg_B = value >> 8;
    regs.reg_C = value & LOWERBITS;
}
void setRegDE(MainRegisters regs, uint16_t value) {
    regs.reg_D = value >> 8;
    regs.reg_E = value & LOWERBITS;
}
void setRegHL(MainRegisters regs, uint16_t value) {
    regs.reg_H = value >> 8;
    regs.reg_L = value & LOWERBITS;
}
