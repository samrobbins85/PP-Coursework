# Programming Paradigms Coursework

The goal of this coursework is to produce Conway's Game of Life in C.

To do this, you will construct a dynamically-linked library `libgol.so` which implements a Game of Life, and a program `gameoflife` that calls the library for all its key functionality.

## Component 1 - Dynamically-linked library

In `gol.h` devise an appropriate structure `struct universe` to hold the universe of cells that you need to keep track of.

Create a file `gol.c` that implements the following features:

1. `read_in_file()` reads in the file from the filepointer `infile` and stores the universe in the structure pointed to by `u`. You must use dynamic memory allocation.
2. `write_out_file()` writes the content of the universe pointed to by `u` into the file from the file pointer `outfile`
3. `is_alive` returns 1 if the cell in that column and row is alive and 0 otherwise
4. `will_be_alive()` returns 1 if that cell in that column and row will be alive in the next generation and 0 otherwise, assuming that cells outside the universe are always dead
5. `will_be_alive_torus()` returns 1 if the cell in that column and row will be alive in the next generation and 0 otherwise, assuming a torus topology
6. `evolve()` changes the universe from the current generation to the next generation. It used the function pointed to by the function pointer `rule`
7. `print_statistics()` should calculate the percentage of cells that are alive in the current generation and the average percentage that have been alive in all the generations so far

Your library should support having multiple universe structures in memory at a time. In case of errors, print a message to `stderr` and exit the current program with a non-zero error code.

## Component 2 - Command-line program

Provide a command line program `gameoflife` to use your library, with the source code `gameoflife.c`. Make sure your program uses the functions in `gol.h` rather than manipulating universe structures directly. Support the following command line switches:

- `-i input_filename` to specify that the initial generation of the universe should be read from a file. If this option is not selected, you should let the user type in the input
- `-o output_filename` to specify a file into which the final generation should be output. If this option is not specified, you should output the final generation on the screen
- `-g number_of_generations` to specify the number of new generations for which the game should be run (set to 5 if this option is not given)
- `-s` to print statistics after the final generation has been output
- `-t` to use the torus topology for the rule. If this is not specified, use the rule for the cells outside the universe being permanently dead

Command-line options can be given in any order. You must use a switch statement to help you parse them.

### Component 3 - Build System

Provide a `Makefile` to compile your library and your command-line program. In your Makefile, use the `-Wall -Wextra -pedantic -std-c11` options each time you call `gcc`. Your code should compile without any warnings or errors. Have rules for creating an object file from each `.c` file, for creating your dynamically linked library `libgol.so` and for creating your command line program `gameoflife`. Using the command `make` should compile your program to a file called `gameoflife` and your library `libgol.so`, both in the current folder. Running `make clean` should delete all files produced during compilation.
