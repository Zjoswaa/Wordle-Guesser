cmake_minimum_required(VERSION 3.27)
project(Wordle_Guesser)

set(CMAKE_CXX_STANDARD 17)

if(DEBUG)
    add_definitions(-DDEBUG=1)
endif (DEBUG)

add_executable(${PROJECT_NAME}
        color.h
        constants.h
        container.h
        container.cpp
        guesser.h
        guesser.cpp
        main.cpp)
