# Wordle Guesser
Tool that can guess wordle solution based on your input and the given results.
It uses a terminal-based GUI to set wordsize, guess count and to input the results that Wordle gives you.
It can currently only show the possible solutions based on your inputs. The functionality to calculate the best next guess still needs to be made.

Currently only works on Windows compilers because I use the `conio.h` library for key inputs. For Linux I need to use a different method of getting keyboard input.

Text files `guesses.txt` and `solutions.txt` can be used when prompted. You can also use your own.
Make sure they contain 1 word per line, all words are the same size and all words are the size of the word size you gave earlier, this is checked when the files are read.

Make sure the `guesses.txt` and `solutions.txt` files are in the same directory as the executable when running. This makes it easier to specify the files when prompted.

---
## Usage
### Windows
In the root directory, run `cmake -S .\src\ -B .\build\ `. This will generate the build files, generally either Visual Studio solution files or a Makefile.

If a Makefile was made `cd .\build\ && make`. Then `.\Guesser.exe` to run the program.

If a Visual Studio Solution was made. Open `Guesser.sln` located in the `build` directory. Then build the project in Visual Studio.
### Linux
In the root directory, run `cmake -S ./src/ -B ./build/`. This will generate the build files. For example a Makefile.

`cd ./build/ && "build command"`. For example if a Makefile was made `cd ./build/ && make`. Then `./Guesser` to run the program.
> **_NOTE:_**  The Linux version can compile but does not work properly yet because of the `conio.h` library not being available for Linux.

---
## Wordlist sources
[solutions.txt](https://gist.github.com/cfreshman/a03ef2cba789d8cf00c08f767e0fad7b)

[guesses.txt](https://gist.github.com/cfreshman/d97dbe7004522f7bc52ed2a6e22e2c04)
