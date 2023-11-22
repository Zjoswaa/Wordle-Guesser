# Wordle Guesser

Tool that can guess wordle solution based on your input and the given results.
It uses a terminal-based GUI to set wordsize, guess count and to input the results that Wordle gives you.
It can currently only show the possible solutions based on your inputs. The functionality to calculate the best next guess still needs to be made.

Currently only works on Windows compilers because I use the `conio.h` library for key inputs. For Linux I need to use a different method of getting keyboard input.

Text files "guesses.txt" and "solutions.txt" can be used when prompted. You can also use your own, make sure they contain 1 word per line, all words are the same size and all words are the size of the word size you gave earlier, this is checked when the files are read.

## Usage

Use `make` to start compilation, then run `Guesser.exe` (Windows) or `./Guesser` (Linux) to run.

## Wordlist sources

solutions.txt: https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b

guesses.txt: https://gist.github.com/cfreshman/d97dbe7004522f7bc52ed2a6e22e2c04
