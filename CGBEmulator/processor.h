//
//  processor.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef processor_h
#define processor_h

#include <stdio.h>
#include "main_registers.h"

typedef struct processor {
    mainRegisters regs;
    uint16_t currentInstruction;
} processor;

#endif /* processor_h */
