#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include "golcompute.h"


/* Compile time defined variables that relate to DISPLAY*/
#define MIN_YDIM 20 // min number of lines in cli
#define MIN_XDIM 50 // min number of columns in cli
#define WIN_MARGINS 2 // margin between windows
#define WIN2WIN_SEPARATION 2 // separation between upper and lower window
#define BEGIN_Y_CELLGRID 1 // line from the top at wich the grid starts
#define NLINES_INFOWIN 3 // Number of lines the information window will have
#define CELL_FILL ' ' // char with which cells will be filled when displayed


void checkdims (int y, int x)
{
    /* Check if the terminal size is large enough for gol to run. If not, exit
    the program. y actually stands for lines and x for columns. */

    if (y < MIN_YDIM || x < MIN_XDIM)
    {
        endwin(); // end ncurses before exiting!
        fprintf(stderr, "CLI is too small. Enlarge it and try again.\n");
        exit(EXIT_FAILURE);
    }
}

WINDOW* setup_cellgrid_window (int ymax, int xmax)
{
    /////////////////////////////////////////////////
    // Create grid window that will hold the cells //
    /////////////////////////////////////////////////
    int nlines_grid = ymax - BEGIN_Y_CELLGRID - WIN2WIN_SEPARATION - NLINES_INFOWIN; // number of lines the grid is allowed to have without overflowing through the bottom
    int ncols_grid = xmax - WIN_MARGINS*2;
    WINDOW* gridwin = newwin(nlines_grid, ncols_grid, BEGIN_Y_CELLGRID, WIN_MARGINS); 
    box(gridwin, 0, 0);
    
    refresh();
    wrefresh(gridwin);

    return gridwin;
}

WINDOW* setup_info_window (int ymax, int xmax)
{
    ///////////////////////////////////////////////////////////////
    // Create information window (for file name, generations...) //
    ///////////////////////////////////////////////////////////////
    int ncols_inf = xmax - WIN_MARGINS*2;
    int nlines_grid = ymax - BEGIN_Y_CELLGRID - WIN2WIN_SEPARATION - NLINES_INFOWIN; // number of lines the grid is allowed to have without overflowing through the bottom
    int begin_y_inf = nlines_grid + WIN2WIN_SEPARATION;
    WINDOW* infowin = newwin(NLINES_INFOWIN, ncols_inf, begin_y_inf, WIN_MARGINS); 
    box(infowin, 0, 0);
    mvwprintw(infowin, 1, WIN_MARGINS, "text2");
    
    refresh();
    wrefresh(infowin);

    return infowin;
}

void init_ncurses (int* ymax, int* xmax)
{
    // Start ncurses
    initscr();

    // Don't echo() while getch is called
    noecho();

    // Check if terminal supports colors
    if (!has_colors())
    {
        printw("Your terminal does not support colors. Exiting at key press.\n");
        getch();
        endwin(); // end ncurses before exiting!
        exit(EXIT_FAILURE);
    }
    start_color();
    
    /* Types of COLORS:
        COLOR_BLACK   0
        COLOR_RED     1
        COLOR_GREEN   2
        COLOR_YELLOW  3
        COLOR_BLUE    4
        COLOR_MAGENTA 5
        COLOR_CYAN    6
        COLOR_WHITE   7
    */

    /* Types of ATTRIBUTES:
        A_NORMAL        Normal display (no highlight)
        A_STANDOUT      Best highlighting mode of the terminal.
        A_UNDERLINE     Underlining
        A_REVERSE       Reverse video
        A_BLINK         Blinking
        A_DIM           Half bright
        A_BOLD          Extra bright or bold
        A_PROTECT       Protected mode
        A_INVIS         Invisible or blank mode
        A_ALTCHARSET    Alternate character set
        A_CHARTEXT      Bit-mask to extract a character
        COLOR_PAIR(n)   Color-pair number n 
    */


    // Get terminal screen size
    getmaxyx(stdscr, *ymax, *xmax);
    // Check if the terminal size is large enough for gol to run
    checkdims(*ymax, *xmax);
}

void display (WINDOW* fieldwin, WINDOW* infowin, CELL** field, int nrows, int ncols)
{
    // Put cells visible in terminal
    int ymax_grid, xmax_grid, ymin_grid, xmin_grid, x, y, i, j;
    getmaxyx(fieldwin, ymax_grid, xmax_grid);
    getbegyx(fieldwin, ymin_grid, xmin_grid);
    
    wattron(fieldwin, A_STANDOUT);
    for (x = ymin_grid, i = 0; x < ymax_grid-1; x++, i++) 
        for (y = xmin_grid, j = 0; y < xmax_grid-2; y++, j++)
            if (field[i][j].current_state)
                mvwaddch(fieldwin, x, y, CELL_FILL);
    wattroff(fieldwin, A_STANDOUT);

    wrefresh(fieldwin);
    wrefresh(infowin);
}

// int main (int argc, char* argv[]) 
// {
//     int ymax, xmax;
//     init_ncurses (&ymax, &xmax);
    
    
//     WINDOW* cellgrid_win = setup_cellgrid_window(ymax, xmax);
//     WINDOW* info_win = setup_info_window(ymax, xmax);


//     // display (WINDOW* fieldwin, WINDOW* infowin, CELL** field, int nrows, int ncols);
    

//     // getch so the program doesn't exit straight away
//     wgetch(cellgrid_win);

//     // End ncurses
//     endwin();
    

//     return (1);
// }