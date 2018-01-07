//
//  decoder.h
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#ifndef decoder_h
#define decoder_h

#include <stdio.h>
#include "constants.h"
#include "main_registers.h"
#include "main_memory.h"

void decodeInstruction(byte opcode, MainRegisters *mainRegs, MainMemory *mainMemory);
#endif /* decoder_h */
