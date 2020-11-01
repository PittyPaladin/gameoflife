#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h> // to include sleep
#include "golcompute.h"
#include "goldisp.h"

int main (int argc, char* argv[]) 
{
    // Initialize ncurses
    init_ncurses (&nrows, &ncols);

    // Display the start menu
    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);
    char* initconf_path = show_menu (ymax, xmax);

    // Load the cells of the initial configuration
    int initcells_rows, initcells_cols;
    CELL** init_cells = load_initconfig (initconf_path, &initcells_rows, &initcells_cols);
    free (initconf_path);

    // Setup cell grid and bottom information windows in ncurses
    WINDOW* cellgrid_win = setup_cellgrid_window (nrows, ncols);
    WINDOW* info_win = setup_info_window (nrows, ncols);

    // Allocate memory dynamically for 2D array of cells
    CELL** grid = cellsmalloc (nrows, ncols);     
    
    // Fill this array with dead cells
    zerofill (grid, nrows, ncols);

    // Put the initial configuration in the 2D array of cells
    place_cells (grid, init_cells, nrows, ncols, initcells_rows, initcells_cols);
    
   
    // Display to terminal the initial state
    int gen = 0;
    display (cellgrid_win, info_win, grid, nrows, ncols, gen);
    gen += 1;


    // Start the main loop
    while (1)
    {
        // Go for all cells in the grid and compute their new state after one generation
        next_generation(grid, nrows, ncols);

        // Change new state to current state to ready up for next generation
        new_state2current_state(grid, nrows, ncols);

        // Display to console
        display (cellgrid_win, info_win, grid, nrows, ncols, gen);

        usleep(1000*100); // or it will go too fast
        gen += 1;
    }


    // getch so the program doesn't exit straight away
    wgetch(cellgrid_win);

    // Liberate the memory
    freemem (grid, nrows);

    // End ncurses
    endwin();

    return (1);
}