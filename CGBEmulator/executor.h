//
//  executor.h
//  CGBEmulator
//
//  Created by Peter Fetros on 1/2/18.
//  Copyright © 2018 Peter Fetros. All rights reserved.
//

#ifndef executor_h
#define executor_h

#include <stdio.h>

void load_8BitRegister_WithRegister(uint8_t *destination, uint8_t *source);
void load_8BitRegister_With8BitData(uint8_t *destination, uint8_t data);

#endif /* executor_h */
