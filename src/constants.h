#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <iostream>

#define WIN_KEY_UP 72
#define WIN_KEY_DOWN 80
#define WIN_KEY_LEFT 75
#define WIN_KEY_RIGHT 77
#define WIN_ENTER 13

const std::string DEFAULT_BACKGROUND = "\033[49m";
const std::string DEFAULT_FOREGROUND = "\033[39m";
const std::string WHITE_BACKGROUND = "\033[107m";
const std::string ORANGE_FOREGROUND = "\033[33m";
const std::string GREEN_FOREGROUND = "\033[92m";
const std::string GREY_FOREGROUND =  "\033[90m";
const std::string DEFAULT_VALID_GUESSES_FILE_NAME = "";
const std::string DEFAULT_WORDLIST_FILE_NAME = "";

#endif