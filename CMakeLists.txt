cmake_minimum_required(VERSION 3.27)
project(Guesser)
set(CMAKE_CXX_STANDARD 17)

if(DEBUG)
    add_definitions(-DDEBUG=1)
endif (DEBUG)

add_subdirectory(src)
