//
//  debug_strings.h
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#ifndef debug_strings_h
#define debug_strings_h

#include "constants.h"

char* getRegisterTypeDebugString(enum REGISTERTYPE regType);
char* getConditionalsDebugString(enum CONDITIONALS conditionalType);
char* getOpcodeDebugString(enum OPCODE_TYPE opcodeType);

#endif /* debug_strings_h */
