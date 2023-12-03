cmake_minimum_required(VERSION 3.27)
project(Wordle_Guesser)

set(CMAKE_CXX_STANDARD 17)

if(DEBUG)
    add_definitions(-DDEBUG=1)
endif (DEBUG)

add_executable(Wordle_Guesser
        src/color.h
        src/constants.h
        src/container.h
        src/container.cpp
        src/guesser.h
        src/guesser.cpp
        src/main.cpp)
