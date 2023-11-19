#include "guesser.h"

Guesser::Guesser() {
    clearTerminal();
    setWordSize();
    setGuessCount();
    initGrid();

    //std::cout << wordMatchesGOGCode("woewi", "wawer", std::vector<Color> {GREEN, GREY, GREY, ORANGE, GREY});

//    std::vector<Color> v = calculateColorResult("wowal", "water");
//    for (unsigned int i = 0; i < v.size(); i++) {
//        if (v[i] == 0) {
//            std::cout << "GREY ";
//        } else if (v[i] == 1) {
//            std::cout << "ORANGE ";
//        } else {
//            std::cout << "GREEN ";
//        }
//    }
//    std::cout << std::endl;

    initValidGuessesList();
//    checkVector(validGuessesList);
    initWordList();
//    checkVector(wordList);
    clearTerminal();

//    orangeLetters.push_back(std::make_pair('t',0));
//    orangeLetters.push_back(std::make_pair('h',1));
//    orangeLetters.push_back(std::make_pair('r',2));
//    std::cout << wordMatchesOrange("tethe");

//    greenLetters.push_back(std::make_pair('t',0));
//    greenLetters.push_back(std::make_pair('h',1));
//    greenLetters.push_back(std::make_pair('r',2));
//    std::cout << wordMatchesGreen("thaax");

    for (unsigned int i = 0; i < guessCount; i++) {
        inputWord(i);
        editColors(i);
        updateGreyLetters(i);
        updateOrangeLetters(i);
        updateGreenLetters(i);
        updateWordList();
        std::cout << "Remaining possible solutions: " << wordList.size() << std::endl;
        if (true) {
            for (unsigned int j = 0; j < wordList.size(); j++) {
                std::cout << wordList[j] << " ";
            }
        }
        std::cout << std::endl;
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Best next guess: " << bestGuessMRC(wordList, validGuessesList);
        auto t2 = std::chrono::high_resolution_clock::now();
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        std::cout << " (took: " << ms_int.count() / 1000 << " sec)" << std::endl;

//        std::cout << "Grey: " << greyLetters << std::endl;
//        std::cout << "Orange: ";
//        for (unsigned int j = 0; j < orangeLetters.size(); j++) {
//            std::cout << orangeLetters[j].first << " " << orangeLetters[j].second << " ";
//        }
//        std::cout << std::endl;
//        std::cout << "Green: ";
//        for (unsigned int j = 0; j < greenLetters.size(); j++) {
//            std::cout << greenLetters[j].first << " " << greenLetters[j].second << " ";
//        }
//        std::cout << std::endl;
//
//
//        std::cout << "Remaining possible solutions: " << wordList.size() << std::endl;
//        for (unsigned int j = 0; j < wordList.size(); j++) {
//            std::cout << wordList[j] << " ";
//        }
//        std::cout << std::endl;
    }
}

void Guesser::initGrid() {
    grid = std::vector<std::vector<Container>>(guessCount, std::vector<Container>(wordSize));
}

void Guesser::inputWord(unsigned int n) {
    std::string input;
    while (true) {
        std::cout << DEFAULT_BACKGROUND;
        std::cout << DEFAULT_FOREGROUND;
        std::cout << "Word " << n+1 << ": ";
        std::cin >> input;
        // Check input size
        if (input.size() != wordSize) {
            std::cout << "Input a " << wordSize << "-character word" << std::endl;
            continue;
        }
        // Check for invalid characters
        if (!containsOnlyLetters(input)) {
            std::cout << "\"" << input << "\" contains an invalid character" << std::endl;
            continue;
        }
        // Check if the word is a valid guess
        if (!isValidGuess(input)) {
            std::cout << "\"" << input << "\" is not in the valid guesses list" << std::endl;
            continue;
        }
        break;
    }
    // Here the word is the correct size and contains valid characters
    guessedWords.push_back(input);
    for (unsigned int i = 0; i < wordSize; i++) {
        // If a character is uppercase
        if (input[i] >= 'A' && input[i] <= 'Z') {
            // Convert it to lowercase (add 32) and put it in the grid
            grid[n][i].letter = input[i] + 32;
        } else {
            // Else its lowercase so just put it in the grid
            grid[n][i].letter = input[i];
        }
    }
}

bool Guesser::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void Guesser::editColors(unsigned int n) {
    unsigned int selectedLetter = 0;
    int c;
    bool loop = true;
    clearTerminal();
    std::cout << "Left/right arrow: select letter, up/down arrow: change color, enter: confirm" << std::endl;
    printGridSelected(n, selectedLetter);
    while (loop) {
        switch((getch())) {
            case KEY_UP:
//                std::cout << "up" << std::endl;
                switch (grid[n][selectedLetter].color) {
                    case GREY:
                        grid[n][selectedLetter].color = ORANGE;
                        break;
                    case ORANGE:
                        grid[n][selectedLetter].color = GREEN;
                        break;
                    case GREEN:
                        grid[n][selectedLetter].color = GREY;
                        break;
                }
                clearTerminal();
                std::cout << "Left/right arrow: select letter, up/down arrow: change color, enter: confirm" << std::endl;
                printGridSelected(n, selectedLetter);
//                for (unsigned int i = 0; i < wordSize; i++) {
//                    std::cout << grid[n][i].color;
//                }
//                std::cout << std::endl;
                break;
            case KEY_DOWN:
//                std::cout << "down" << std::endl;
                switch (grid[n][selectedLetter].color) {
                    case GREY:
                        grid[n][selectedLetter].color = GREEN;
                        break;
                    case ORANGE:
                        grid[n][selectedLetter].color = GREY;
                        break;
                    case GREEN:
                        grid[n][selectedLetter].color = ORANGE;
                        break;
                }
                clearTerminal();
                std::cout << "Left/right arrow: select letter, up/down arrow: change color, enter: confirm" << std::endl;
                printGridSelected(n, selectedLetter);
//                for (unsigned int i = 0; i < wordSize; i++) {
//                    std::cout << grid[n][i].color;
//                }
//                std::cout << std::endl;
                break;
            case KEY_LEFT:
                if (selectedLetter == 0) {
                    selectedLetter = wordSize - 1;
                } else {
                    selectedLetter--;
                }
                clearTerminal();
                std::cout << "Left/right arrow: select letter, up/down arrow: change color, enter: confirm" << std::endl;
                printGridSelected(n, selectedLetter);
                break;
            case KEY_RIGHT:
                if (selectedLetter == wordSize - 1) {
                    selectedLetter = 0;
                } else {
                    selectedLetter++;
                }
                clearTerminal();
                std::cout << "Left/right arrow: select letter, up/down arrow: change color, enter: confirm" << std::endl;
                printGridSelected(n, selectedLetter);
                break;
            case ENTER:
                clearTerminal();
                printGrid(n);
                loop = false;
            default:
                break;
        }
    }
}

void Guesser::printGridSelected(unsigned int n, unsigned int selected) {
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j < wordSize; j++) {
            // Print the letter with a white background if its selected and in the last row
            if (j == selected && i == n) {
                std::cout << WHITE_BACKGROUND;
            } else {
                std::cout << DEFAULT_BACKGROUND;
            }
            // Print every letter with its respective color by changing the current output stream color
            switch (grid[i][j].color) {
                case GREY:
                    std::cout << GREY_FOREGROUND;
                    break;
                case ORANGE:
                    std::cout << ORANGE_FOREGROUND;
                    break;
                case GREEN:
                    std::cout << GREEN_FOREGROUND;
                    break;
            }
            std::cout << grid[i][j].letter;
        }
        std::cout << std::endl;
    }
    std::cout << DEFAULT_FOREGROUND;
    std::cout << DEFAULT_BACKGROUND;
}

void Guesser::printGrid(unsigned int n) {
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j < wordSize; j++) {
            switch (grid[i][j].color) {
                case GREY:
                    std::cout << GREY_FOREGROUND;
                    break;
                case ORANGE:
                    std::cout << ORANGE_FOREGROUND;
                    break;
                case GREEN:
                    std::cout << GREEN_FOREGROUND;
                    break;
            }
            std::cout << grid[i][j].letter;
        }
        std::cout << std::endl;
    }
    std::cout << DEFAULT_FOREGROUND;
}

void Guesser::clearTerminal() {
    //std::cout << "\x1B[2J\x1B[H";
    if (system("cls")) {
        system("clear");
    }
}

bool Guesser::isNumerical(std::string s) {
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

void Guesser::setWordSize() {
    std::string input;
    while (true) {
        std::cout << "Word size: ";
        std::cin >> input;
        if (!isNumerical(input)) {
            std::cout << "Invalid number" << std::endl;
            continue;
        } else if (!checkOverflow(input)) {
            std::cout << "Number too big" << std::endl;
            continue;
        } else if (input.size() == 1 && input[0] == '0') {
            std::cout << "Enter a positive non-zero number" << std::endl;
            continue;
        } else {
            break;
        }
    }
    wordSize = 0;
    for (unsigned int i = 0; i < input.length(); i++) {
        wordSize *= 10;
        wordSize += (int(input[i]) - '0');
    }
}

void Guesser::setGuessCount() {
    std::string input;
    while (true) {
        std::cout << "Guess count: ";
        std::cin >> input;
        if (!isNumerical(input)) {
            std::cout << "Invalid number" << std::endl;
            continue;
        } else if (!checkOverflow(input)) {
            std::cout << "Number too big" << std::endl;
            continue;
        } else if (input.size() == 1 && input[0] == '0') {
            std::cout << "Enter a positive non-zero number" << std::endl;
            continue;
        } else {
            break;
        }
    }
    guessCount = 0;
    for (unsigned int i = 0; i < input.length(); i++) {
        guessCount *= 10;
        guessCount += (int(input[i]) - '0');
    }
}

bool Guesser::checkOverflow(std::string s) {
    // Get the length of UINT_MAX
    unsigned int max = UINT_MAX;
    short maxSize = 0;
    while (max > 0) {
        max /= 10;
        maxSize++;
    }
    // Compare this length to length of s
    if (s.length() > maxSize) {
        return false;
    }

    // Check if the resulting number will cause overflow by checking against big buffer
    unsigned long long buffer = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        buffer *= 10;
        buffer += (int(s[i]) - '0');
    }
    if (buffer > UINT_MAX) {
        return false;
    }
    return true;
}

void Guesser::initValidGuessesList() {
    std::string input;
    while (true) {
        std::cout << "Valid guesses list file name: ";
        std::cin >> input;
        if (readFile(input, validGuessesList)) {
            break;
        }
    }
}

void Guesser::initWordList() {
    std::string input;
    while (true) {
        std::cout << "Wordlist file name: ";
        std::cin >> input;
        if (readFile(input, wordList)) {
            break;
        }
    }
}

bool Guesser::containsOnlyLetters(std::string s) {
    for (unsigned int i = 0; i < wordSize; i++) {
        if (!isLetter(s[i])) {
            return false;
        }
    }
    return true;
}

void Guesser::checkVector(std::vector<std::string> v) {
    std::cout << v.size() << std::endl;
    for (unsigned int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " " << v[i].size() << std::endl;
    }
}

bool Guesser::readFile(std::string fileName, std::vector<std::string> &v) {
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        std::cout << "Couldn't open \"" << fileName << "\"" << std::endl;
        return false;
    }
    v.clear();
    std::string buffer;
    while (file >> buffer) {
        if (buffer.size() != wordSize) {
            std::cout << "Word \"" << buffer << "\" in \"" << fileName << "\" is not " << wordSize << " characters long" << std::endl;
            v.clear();
            file.close();
            return false;
        }
        v.push_back(buffer);
    }
    file.close();
    return true;
}

bool Guesser::isValidGuess(std::string s) {
    for (unsigned int i = 0; i < validGuessesList.size(); i++) {
        if (s == validGuessesList[i]) {
            return true;
        }
    }
    return false;
}

bool Guesser::wordMatchesGrey(std::string word) {
    for (unsigned int i = 0; i < wordSize; i++) {
        if (stringContainsChar(greyLetters, word[i])) {
            return false;
        }
    }
    return true;
}

void Guesser::updateGreyLetters(unsigned int n) {
    greyLetters = "";
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j < wordSize; j++) {
            if (grid[i][j].color == GREY) {
                if (!stringContainsChar(greyLetters, grid[i][j].letter)) {
                    greyLetters.push_back(grid[i][j].letter);
                }
            }
        }
    }
}

bool Guesser::stringContainsChar(std::string s, char c) {
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return true;
        }
    }
    return false;
}

bool Guesser::wordMatchesOrange(std::string word) {
    for (unsigned int i = 0; i < orangeLetters.size(); i++) {
        if (!stringContainsChar(word, orangeLetters[i].first)) {
            return false;
        }
    }
    // Here the word contains at least every orange letter, but they cannot be on the index the orange letter was found or it would have to be a green letter
    for (unsigned int i = 0; i < wordSize; i++) {
        for (unsigned int j = 0; j < orangeLetters.size(); j++) {
            // Every letter that matches cannot have matching indexes
            if (word[i] == orangeLetters[j].first) {
                if (i == orangeLetters[j].second) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Guesser::updateOrangeLetters(unsigned int n) {
    orangeLetters.clear();
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j < wordSize; j++) {
            if (grid[i][j].color == ORANGE) {
                if (!vectorContainsPair(orangeLetters, grid[i][j].letter, j)) {
                    orangeLetters.push_back(std::make_pair(grid[i][j].letter, j));
                }
            }
        }
    }
}

bool Guesser::wordMatchesGreen(std::string word) {
    for (unsigned int i = 0; i < greenLetters.size(); i++) {
        if (word[greenLetters[i].second] != greenLetters[i].first) {
            return false;
        }
    }
    return true;
}

void Guesser::updateGreenLetters(unsigned int n) {
    greenLetters.clear();
    for (unsigned int i = 0; i <= n; i++) {
        for (unsigned int j = 0; j < wordSize; j++) {
            if (grid[i][j].color == GREEN) {
                if (!vectorContainsPair(greenLetters, grid[i][j].letter, j)) {
                    greenLetters.push_back(std::make_pair(grid[i][j].letter, j));
                }
            }
        }
    }
}

void Guesser::updateWordList() {
    std::vector<std::string> temp;
    for (unsigned int i = 0; i < wordList.size(); i++) {
        if (wordMatchesGrey(wordList[i]) && wordMatchesOrange(wordList[i]) && wordMatchesGreen(wordList[i])) {
            temp.push_back(wordList[i]);
        }
    }
    wordList = temp;
}

bool Guesser::vectorContainsPair(std::vector<std::pair<char, unsigned int>> v, char c, unsigned int i) {
    for (unsigned int _i = 0; _i < v.size(); _i++) {
        if (v[_i].first == c && v[_i].second == i) {
            return true;
        }
    }
    return false;
}

std::string Guesser::bestGuessMRC(std::vector<std::string> possibleSolutions, std::vector<std::string> validGuesses) {
    // For every valid guess do the following:
    // - Check the count of grey, orange and green letters that the guess would have against every possible solution
    // - Based on these results, filter the possible solutions that abide by this grey-orange-green result and save how many there are
    // - Take the highest of these counts and bind this count to the guess done in the first step

    // Finally, every valid guess has a count bound to it, return the guess that has the lowest.
    // This guess, in the worst-case scenario, will leave the least amount of possible solutions for the next guess.

}

std::vector<Color> Guesser::calculateColorResult(std::string guess, std::string solution) {
    std::vector<Color> toReturn;
    for (unsigned int i = 0; i < wordSize; i++) {
        if (guess[i] == solution[i]) {
            toReturn.push_back(GREEN);
        } else {
            toReturn.push_back(GREY);
        }
    }
    for (unsigned int i = 0; i < wordSize; i++) {
        if (stringContainsChar(solution, guess[i]) && guess[i] != solution[i]) {
            for (unsigned int j = 0; j < wordSize; j++) {
                if (solution[j] == guess[i] && toReturn[j] != GREEN) {
                    toReturn[i] = ORANGE;
                }
            }
        }
    }
    return toReturn;
}

bool Guesser::wordMatchesGOGCode(std::string word, std::string solution, std::vector<Color> code) {
    for (unsigned int i = 0; i < wordSize; i++) {
        if (code[i] == GREEN) {
            if (!stringContainsChar(word, solution[i])) {
                return false;
            }
        } else if (code[i] == GREY) {
            for (unsigned int j = 0; j < wordSize; j++) {
                if (solution[j] == word[i] && code[j] == GREEN) {
                    if (stringContainsChar(word, solution[i])) {
                        return false;
                    }
                }
            }
        }
    }
    for (unsigned int i = 0; i < wordSize; i++) {
        if (code[i] == ORANGE) {
            if (!stringContainsChar(word, solution[i]) || word[i] == solution[i]) {
                return false;
            } else {
                for (unsigned int j = 0; j < wordSize; j++) {
                    if (solution[j] == word[i] && code[j] != GREEN) {
                        return true;
                    }
                }
                return false;
            }
        }
    }
    return false;
}

bool Guesser::guessDone(std::string word) {
    for (unsigned int i = 0; i < guessedWords.size(); i++) {
        if (guessedWords[i] == word) {
            return true;
        }
    }
    return false;
}