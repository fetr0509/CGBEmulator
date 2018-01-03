//
//  main.c
//  CGBEmulator
//
//  Created by Peter Fetros on 12/21/17.
//  Copyright © 2017 Peter Fetros. All rights reserved.
//

#include <stdio.h>
#include "decoder.h"

struct test {
    uint8_t test1;
    uint8_t test2;
};

extern int CompileTimeAssert[ sizeof(struct test) == 2 * sizeof(uint8_t) ? 1 : -1];

int main(int argc, const char * argv[]) {
    struct test Test = {10,9};
    
    printf("T1: %i\n",Test.test1);
    printf("T1: %i\n\n",Test.test2);
    
    uint8_t *p = &Test;
    //p =  ((uint8_t*) p + sizeof(uint8_t));
    

    printf("Size: %i\n", (uint8_t)(*p));
    //printf("T1: %i",Test);
}
