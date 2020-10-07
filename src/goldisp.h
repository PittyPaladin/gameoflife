#include <ncurses.h>

int nrows, ncols;
void init_ncurses (int* nrows, int* ncols);
void checkdims (int y, int x);

WINDOW* setup_cellgrid_window (int ymax, int xmax);
WINDOW* setup_info_window (int ymax, int xmax);

void display (WINDOW* fieldwin, WINDOW* infowin, CELL** field, int nrows, int ncols);