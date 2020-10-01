#include <stdio.h>
#include <stdlib.h>

int main ()
{
    // The cell struct. New type is customary to write it in caps
    typedef struct {
        int alive;
        int pos_x;
        int pos_y;
    } CELL;

    // Array of pointers of type CELL
    int nrows = 2;
    int ncols = 3;

    CELL** field = (CELL**) malloc(nrows*sizeof(CELL*));
    
    // Allocate array of CELL per each array (row)
    for (int i = 0; i < nrows; ++i)
        field[i] = (CELL*) malloc(ncols*sizeof(CELL));
    
    // Test: fill the 2D array up
    CELL fillcell;
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