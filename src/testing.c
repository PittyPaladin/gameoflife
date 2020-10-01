#include <stdio.h>
#include <stdlib.h>

int main ()
{
    // The cell struct
    typedef struct {
        int alive;
        int pos_x;
        int pos_y;
    } cell;

    // Array of pointers of type cell
    int nrows = 2;
    int ncols = 3;

    cell** field = (cell**) malloc(nrows*sizeof(cell*));
    
    // Allocate array of cell per each array (row)
    for (int i = 0; i < nrows; ++i)
        field[i] = (cell*) malloc(ncols*sizeof(cell));
    
    // Test: fill the 2D array up
    cell fillcell;
    fillcell.alive = 1; 
    fillcell.pos_x = 0; 
    fillcell.pos_y = 1;
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            field[i][j] = fillcell;
    
    // Test: print the 2D array
    for (int i = 0; i < nrows; ++i){
        for (int j = 0; j < ncols; ++j){
            printf("%d ", field[i][j].alive);
        }
        printf("\n");
    }

    // Free the memory
    for (int i = 0; i < nrows; ++i)
        free(field[i]);
    free(field);

    return 1;
}