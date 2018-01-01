//
//  main.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include <stdio.h>
#include "instruction.h"
#include "decoder.h"
#include "debug_functions.h"

int main(int argc, const char * argv[]) {
    struct Instruction instruction = {-1,-1,-1,-1,-1,-1};
    
    for (int i = 0; i <= 0xFF; ++i) {
        decodeInstruction(i, &instruction);
        printInstructionInformation(&instruction);
    }
}
