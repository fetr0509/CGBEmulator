cmake_minimum_required(VERSION 3.9)
project(CGBEmulator)

set(CMAKE_CXX_STANDARD 11)

if(APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I/usr/local/include/SDL2 -D_THREAD_SAFE")
    include_directories(${PROJECT_SOURCE_DIR}/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/osx)
endif()

if(NOT APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lmingw32 -lSDLmain -lSDL")
    set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc")
    include_directories(${PROJECT_SOURCE_DIR}/include)
    link_directories(${PROJECT_SOURCE_DIR}/lib/windows)
endif()

add_executable(CGBEmulator
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
        CGBEmulator/main_registers.h
        CGBEmulator/game_loop.c
        CGBEmulator/game_loop.h
        CGBEmulator/lcd.c
        CGBEmulator/lcd.h)

if(APPLE)
    target_link_libraries(CGBEmulator -L/usr/local/lib -lSDL2)
endif()

if(NOT APPLE)
    target_link_libraries(CGBEmulator mingw32 SDL2main SDL2)
endif()
