# What is this repo
This is Conway's Game of Life written in C, and displayed to terminal using ncurses library. This project is a task for the Embedded and Real Time Systems subject from the MSc on Automatic Control at UPC.

# How to run it
In the root folder, create a file called `build` and another one called `bin`. Then, open the terminal and run `make`. The executable will be placed at `bin`. To run it, just type `./bin/gameoflife`. The program will go on forever. To stop it, just exit the program by hitting **ctrl + c**.

# How to introduce initial configurations
Create a file with whatever name you like, with the file extension .gol, and save it in the folder `configs`. Remember that it is filled with either 1s or 0s and columns must be the same size. Do not forget to add an INTRO (i.e. hit the ENTER key) at the end of the last line.