#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // to include sleep
#include "golcompute.h"


/* Preprocessor defined variables that relate to DISPLAY*/
#define MIN_YDIM 20 // min number of lines in cli
#define MIN_XDIM 50 // min number of columns in cli
#define WIN_MARGINS 2 // margin between windows
#define WIN2WIN_SEPARATION 2 // separation between upper and lower window
#define BEGIN_Y_CELLGRID 1 // line from the top at wich the grid starts
#define BEGIN_Y_MENU 3 // line from the top at wich the menu starts
#define NLINES_INFOWIN 3 // Number of lines the information window will have
#define CELL_FILL ' ' // char with which cells will be filled when displayed


char* show_menu (int ymax, int xmax)
{
    /* Obtain the maximum sizes of the windows to used them for the windows of 
     menu. */
         
    // Get the list of files that could serve as initial configs
    int nfiles;
    char** fnames = listfiles (&nfiles);
    printf(" ");

    // Create a windows for the menu
    int ncols_menu = xmax - WIN_MARGINS*2;
    // fprintf(stdout, " "); // I don't know why, if this line is not here, menu breaks
    WINDOW* menuwin = newwin(nfiles+3, ncols_menu, BEGIN_Y_MENU, WIN_MARGINS); //int nlines, int ncols, int begin_y, int begin_x
    box(menuwin, 0, 0);

    // Print a warming welcome title
    attron(A_REVERSE);
    mvwprintw(stdscr, BEGIN_Y_MENU - 2, WIN_MARGINS, "Welcome to Conway's Game of Life");
    attroff(A_REVERSE);
    mvwprintw(stdscr, BEGIN_Y_MENU - 1, WIN_MARGINS, "Pick an initial state from the menu below:");
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true); //enables the reading of function keys like F1, F2, arrow keys.
    
    
    // Choices of the menu
    int choice;
    int highlight = 0;
    int i;
    while(1)
    {
        for(i = 0; i<nfiles; i++)
        {
            if(i == highlight)
                wattron(menuwin, A_REVERSE); //Hightlight the option selected in the menu
            mvwprintw(menuwin, i + 1, 1, fnames[i]); //Print the choice highlighted
            wattroff(menuwin, A_REVERSE); //Stop highlighting the option selected
        }

        choice = wgetch(menuwin); //Obtain the choice desired

        switch(choice)
        {
            case KEY_UP:
                if ( highlight>0){ //Limiting the highlight to the first selection if we exceed
                    highlight--;}
                break;
            case KEY_DOWN:
                if ( highlight<nfiles-1){ //Limiting the highlight to the last selection if we exceed
                    highlight++;}
                break;
            default: //In case the user select another key
                break;
        }
        if(choice == 10) // When the key "Enter" is selected, we will choose the opction highlighted
            break;
    }

    usleep(1000*50); 

    //Make sure program waits for exiting
    wborder(menuwin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wclear(menuwin);
    clear();
    wrefresh(menuwin);
    delwin(menuwin);
    refresh();
    
    char* fullpath = (char*) malloc (50*sizeof(char));
    strcpy (fullpath,"./../configs/");
    strcat(fullpath, fnames[highlight]);
    return (fullpath);
}

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
    mvwprintw(infowin, 1, WIN_MARGINS, "Generation: ");
    mvwprintw(infowin, 1, WIN_MARGINS + strlen("Generation: "), "%d", 0);
    
    refresh();
    wrefresh(infowin);

    return infowin;
}

void update_gennumber (WINDOW* infowin, int gen)
{
    /* Update the integer after the word "Generation: " to tell the user at 
    which generation the simulation is at */
    mvwprintw(infowin, 1, WIN_MARGINS + strlen("Generation: "), "%d", gen);
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

void display (WINDOW* fieldwin, WINDOW* infowin, CELL** field, int nrows, int ncols, int generations)
{
    // Put cells visible in terminal
    int ymax_grid, xmax_grid, ymin_grid, xmin_grid, x, y, i, j;
    getmaxyx(fieldwin, ymax_grid, xmax_grid);
    getbegyx(fieldwin, ymin_grid, xmin_grid);
    
    for (x = ymin_grid, i = 0; x < ymax_grid-1; x++, i++) 
        for (y = xmin_grid, j = 0; y < xmax_grid-2; y++, j++)
            if (field[i][j].current_state)
                mvwaddch(fieldwin, x, y, CELL_FILL | A_STANDOUT);
            else
                mvwaddch(fieldwin, x, y, CELL_FILL | A_NORMAL); 

    // Put generation numbers in infowin
    update_gennumber (infowin, generations);

    wrefresh(fieldwin);
    wrefresh(infowin);
}
