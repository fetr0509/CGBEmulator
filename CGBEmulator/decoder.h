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

void decodeInstruction(uint8_t opcode, MainRegisters mainRegs);
#endif /* decoder_h */
