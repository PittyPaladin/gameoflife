# What is this repo
This is Conway's Game of Life written in C, and displayed to terminal using ncurses library. This project is a task for the Embedded and Real Time Systems subject for the MSc on Automatic Control at UPC.

# How to run it
In the root folder, create a file called `build` and another one called `bin` if they don't exist already. Then, open the terminal at the root directory and run `make`. The executable will be placed at `bin`. To run it, just go to the `bin` folder and type `./gameoflife`. The program will go on forever. To stop it, just exit the program by hitting **q**. Note: if you stay in the root folder and run the executable typing `./bin/gameoflife` it won't work.

# How to introduce initial configurations
Create a file with whatever name you like, with the file extension .gol, and save it in the folder `configs`. Remember that it is filled with either 1s or 0s and columns must be the same size. Do not forget to add an INTRO (i.e. hit the ENTER key) at the end of the last line. Look at the existing initial configurations to have an example on how to create your own.