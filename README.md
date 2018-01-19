# CGBEmulator

This is a Game Boy Emulator written in C. 
The focus of this emulator will be to incorporate a wide variety of debugging facilities which allow users and developers
To examine the code execution in multiple ways.

____
## Features

These specific features that this Game boy emulator will have are: 
*  Memory Viewer - Allows the user to see the Game Boy's memory and register status such as current instruction as well as step through the memory
*  Memory Editor - Edit the Game Boy's memory on the fly and search for values within memory.

____
## Testing

*  Using OCLint for linting while developing on Linux. (cMake integration but not execution).
*  Unity for Unit testing.

____
## Resources
Below is a list of resources that were/are being referenced during the design and implementation. Not all of these resources are complete on their own and some hardware resources are related to the Game Boy hardware but not strictly identical.

#### [Game Boy Manual](http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf)
General Reference for memory locations, opcodes, and technical details for the Game Boy. While the opcode reference material is complete it describes the operations vaguely. 

#### [Game Boy CPU (LR35902) instruction set](http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html)
Reference table for opcodes. These tables describe the type of operation and orders them by opcode. This lists the type on instruction, the inputs as well as the instruction length and number of instruction cycles for execution.

#### [Misc info](http://bgb.bircd.org/pandocs.htm#gameboytechnicaldata)
This is another reference manual for the Game Boy. However this manual contains more specific information on the hardware aspects of the Game Boy compared to the Game Boy manual referenced above.

#### [Z80 Reference **(SIMILAR PROCESSOR, NOT IDENTICAL)**](http://www.z80.info/z80syntx.htm#RET)
This is an opcode reference for the Z80 processor which is what the Game Boy's processor was designed after. There are several operations that work differently for the Game Boys processor however most are identical and the operations and side effects are described in much greater detail compared to the resources above.

#### [Opcode Summary](http://www.devrs.com/gb/files/opcodes.html)
This is a shorter summary than the Game Boy CPU instruction set but it a good source for verifying the correct usage of the opcodes.

#### [Blargg's tests](http://gbdev.gg8.se/files/roms/blargg-gb-tests/)
This is a mirror containing test ROMs used to test various aspects of the emulator. These test ROMs are widely used to verify the quality of the emulator and includes test related to all aspects of Game Boy emulation such as timing and sound support.
