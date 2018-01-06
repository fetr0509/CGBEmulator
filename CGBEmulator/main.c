//
//  main.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include <stdio.h>
#include "decoder.h"
#include "constants.h"

int main(int argc, const char * argv[]) {
    for(int i = 0; i < 8;i++) {
        printf("%x ",(1 << i));
           }
}
