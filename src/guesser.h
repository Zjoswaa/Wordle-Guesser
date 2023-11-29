#ifndef GUESSER_H
#define GUESSER_H

// Key press logic uses a different library on Windows (conio.h) and Linux
#ifdef _WIN32
#include <conio.h>
#endif
#ifdef linux
#include <climits>
// TODO: Add a library for Linux key press logic
#endif

#include "color.h"
#include "constants.h"
#include "container.h"
#include <chrono>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Guesser {
public:
    Guesser();

private:
    unsigned int wordSize;
    unsigned int guessCount;
    // Words that are a valid guess
    std::vector<std::string> validGuessesList;
    // Words that are the current possible solutions
    std::vector<std::string> wordList;
    // The wordle grid, default 6 guesses of 5-letter words
    std::vector<std::vector<Container>> grid;
    // The list of characters (string) that holds the letters that are confirmed to not be in the solution
    std::string greyLetters = "";
    // The list of orange marked letters, saved in pairs each containing the letter and the index of the word it was found at
    std::vector<std::pair<char, unsigned int>> orangeLetters;
    // The list of green marked letters, saved in pairs each containing the letter and the index of the word it was found at
    std::vector<std::pair<char, unsigned int>> greenLetters;
    // The guesses that user has already done
    std::vector<std::string> guessedWords;

    // Initializes the grid with containers that contain character '.' and color NONE
    void initGrid();

    // Asks user for input of a word and inserts it into the grid at index n
    void inputWord(unsigned int n);

    // Returns if c is a letter (a-z / A-Z)
    bool isLetter(char c);

    // Edit the colors of word at index n
    void editColors(unsigned int n);

    // Prints the words grid until word n with one letter selected
    void printGridSelected(unsigned int n, unsigned int selected);

    // Prints the words grid until word n
    void printGrid(unsigned int n);

    // Clears the terminal
    void clearTerminal();

    // Checks if s holds only numerical values
    bool isNumerical(std::string s);

    // Asks user for word size, checks if its valid and sets it
    void setWordSize();

    // Asks user for guess count, checks if its valid and sets it
    void setGuessCount();

    // Checks if s will cause overflow when converted to unsigned int, assumes s is numerical
    bool checkOverflow(std::string s);

    // Asks the user for the name of the file containing the valid guess list and reads that file
    void initValidGuessesList();

    // Asks the user for the name of the file containing the wordlist (all possible solutions) and reads that file
    void initWordList();

    // Returns whether s contains only letters, assumes s is wordSize long
    bool containsOnlyLetters(std::string s);

    // Debug to check vector size and size of every element
    void checkVector(std::vector<std::string> v);

    // Tries to write the content of a file to a vector
    bool readFile(std::string fileName, std::vector<std::string> &v);

    // Checks if s is in the valid guesses list
    bool isValidGuess(std::string s);

    // Checks if word matches the current grey letter constraints
    bool wordMatchesGrey(std::string word);

    // Updates the letters that are confirmed to not be in the solution, letters uniquely saved in a string
    void updateGreyLetters(unsigned int n);

    // Checks if s contains c
    bool stringContainsChar(std::string s, char c);

    // Checks if word matches the current orange letter constraints
    bool wordMatchesOrange(std::string word);

    // Updates the letters that are marked orange, letters uniquely saved as pairs containing the letter and the index in the word at which it was found
    void updateOrangeLetters(unsigned int n);

    // Checks if word matches the current green letter constraints
    bool wordMatchesGreen(std::string word);

    // Updates the letters that are marked green, letters uniquely saved as pairs containing the letter and the index in the word at which it was found
    void updateGreenLetters(unsigned int n);

    // Updates the wordlist to contain only possible solutions based on the current grey, orange and green constraints
    void updateWordList();

    // Checks if v contains a pair that contains c and i, used for the orange and green letter vectors
    bool vectorContainsPair(std::vector<std::pair<char, unsigned int>> v, char c, unsigned int i);

    // Calculates the best guess from validGuesses based on the possible solutions, uses a Max Remaining Candidates algorithm (MRC)
    std::string bestGuessMRC(std::vector<std::string> possibleSolutions, std::vector<std::string> validGuesses);

    // Returns the colors the guess g would have if the solution was s
    std::vector<Color> calculateColorResult(std::string guess, std::string solution);

    // Checks if word matches code if solution were the correct word
    bool wordMatchesGOGCode(std::string word, std::string solution, std::vector<Color> code);

    // Checks if guess has already been done
    bool guessDone(std::string word);
};

#endif
