//
//  debug_functions.c
//  CGBEmulator
//
//  Created by Peter Fetros on 1/1/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#include "debug_functions.h"

#include <stdio.h>

#include "debug_strings.h"

void printInstructionInformation(struct Instruction* instruction) {
    printf("Opecode: %x\n",instruction->opcode);
    printf("Opcode Type: %s\n",getOpcodeDebugString(instruction->opcodeType));
    printf("Destination: %s\t\tSource: %s\n",
           getRegisterTypeDebugString(instruction->destinationReg),getRegisterTypeDebugString(instruction->sourceReg));
    printf("Length: %i\t\tDuration: %i\n",instruction->instructionLength,instruction->cycleDuration);
    printf("\n");
}
