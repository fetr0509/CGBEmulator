//
//  main_registers.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include "main_registers.h"

void initializeMainRegisters(MainRegisters *mainRegisters) {
    mainRegisters->reg_A = 0;
    mainRegisters->reg_F = 0;
    mainRegisters->reg_B = 0;
    mainRegisters->reg_C = 0;
    mainRegisters->reg_D = 0;
    mainRegisters->reg_E = 0;
    mainRegisters->reg_H = 0;
    mainRegisters->reg_L = 0;
    mainRegisters->programCounter = 0x100;
    mainRegisters->stackPointer = 0xFFFE;
}
