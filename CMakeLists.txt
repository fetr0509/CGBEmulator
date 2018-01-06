cmake_minimum_required(VERSION 3.9)
project(CGBEmulator)

set(CMAKE_CXX_STANDARD 11)

add_executable(CGBEmulator
        .idea/codeStyles/Project.xml
        .idea/CGBEmulator.iml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        CGBEmulator/constants.h
        CGBEmulator/decoder.c
        CGBEmulator/decoder.h
        CGBEmulator/executor.c
        CGBEmulator/executor.h
        CGBEmulator/flag_helpers.c
        CGBEmulator/flag_helpers.h
        CGBEmulator/main.c
        CGBEmulator/main_memory.c
        CGBEmulator/main_memory.h
        CGBEmulator/main_registers.c
        CGBEmulator/main_registers.h)
