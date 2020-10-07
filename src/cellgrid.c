#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>


/* Compile time-defined variables that relate to DISPLAY*/
#define MIN_YDIM 20 // min number of lines in cli
#define MIN_XDIM 50 // min number of columns in cli
#define WIN_MARGINS 2 // margin between windows
#define WIN2WIN_SEPARATION 2 // separation between upper and lower window
#define BEGIN_Y_CELLGRID 1 // line from the top at wich the grid starts
#define NLINES_INFOWIN 3 // Number of lines the information window will have
#define CELL_FILL ' ' // char with which cells will be filled when displayed


void checkdims(int y, int x)
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

WINDOW* setup_cellgrid_window(int ymax, int xmax)
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

WINDOW* setup_info_window(int ymax, int xmax)
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

int main (int argc, char* argv[]) 
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
    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);
    // Check if the terminal size is large enough for gol to run
    checkdims(ymax, xmax);
    
    WINDOW* cellgrid_win = setup_cellgrid_window(ymax, xmax);
    WINDOW* info_win = setup_info_window(ymax, xmax);


    
    // Test: print some lines
    int ymax_grid, xmax_grid, ymin_grid, xmin_grid;
    getmaxyx(cellgrid_win, ymax_grid, xmax_grid);
    getbegyx(cellgrid_win, ymin_grid, xmin_grid);
    wattron(cellgrid_win, A_STANDOUT);
    for (int i = ymin_grid; i < ymax_grid-1; i++) {
        for (int j = xmin_grid; j < xmax_grid-2; j++){
            mvwaddch(cellgrid_win, i, j, CELL_FILL);
        }
    }
    wattroff(cellgrid_win, A_STANDOUT); // Don't really need it if it's placed at the end
    
    
    
    wrefresh(cellgrid_win);
    wrefresh(info_win);
    



    // getch so the program doesn't exit straight away
    wgetch(cellgrid_win);

    // End ncurses
    endwin();
    

    return 1;
}