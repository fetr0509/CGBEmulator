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

    word cycles;
    
} MainRegisters;

void initializeMainRegisters(MainRegisters *mainRegisters);


#endif /* main_registers_h */
