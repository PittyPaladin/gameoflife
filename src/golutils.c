#include <stdio.h>
#include <stdlib.h>


// The cell struct. New type is customary to write it in caps.
typedef struct {
    int current_state;
    int new_state;
} CELL;

void new_state2current_state (CELL** field, int nrows, int ncols)
{
    for (int i = 0; i < nrows; ++i){
        for (int j = 0; j < ncols; ++j){
            /* Swap state to prepare for next iteration: take the cell's new 
            state and copy it to its current state */
            field[i][j].current_state = field[i][j].new_state;
        }
    }
}

void compute_new_state (CELL** field, int i, int j, int nrows, int ncols)
{
    // Compute the new state for the cell, in other words, let a generation go by

    // RULES //
    /* 1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
       2. Any live cell with two or three live neighbours lives on to the next generation.
       3. Any live cell with more than three live neighbours dies, as if by overpopulation.
       4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction. */

    int neighbours = 0;
    if (i != 0) // North
        neighbours += field[i -1 ][j].current_state;
    if (i != 0 && j != ncols - 1) // Northeast
        neighbours += field[i - 1][j + 1].current_state;
    if (j != nrows - 1) // East
        neighbours += field[i][j + 1].current_state;
    if (j != nrows && i != nrows-1) // Southeast
        neighbours += field[i + 1][j + 1].current_state;
    if (i != nrows-1) // South
        neighbours += field[i + 1][j].current_state;
    if (j != 0 && i != nrows-1) // Southwest
        neighbours += field[i + 1][j - 1].current_state;
    if (j != 0) // West
        neighbours += field[i][j - 1].current_state;
    if (j != 0 && i != 0) // Northwest
        neighbours += field[i - 1][j - 1].current_state;
    
    
    if (field[i][j].current_state == 1 && neighbours < 2) // Rule 1.
        field[i][j].new_state = 0;
    else if (field[i][j].current_state == 1 && neighbours >= 2 && neighbours <= 3) // Rule 2.
        field[i][j].new_state = field[i][j].current_state;
    else if (field[i][j].current_state == 1 && neighbours > 3) // Rule 3.
        field[i][j].new_state = 0;
    else if (field[i][j].current_state == 0 && neighbours == 3) // Rule 4.
        field[i][j].new_state = 1;
}

void next_generation (CELL** field, int nrows, int ncols)
{
    //
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            compute_new_state (field, i, j, nrows, ncols);

}

void freemem (CELL** field, int nrows)
{
    // Free the memory
    for (int i = 0; i < nrows; ++i)
        free(field[i]);
    free(field);
}

CELL** cellsmalloc (int nrows, int ncols)
{
    // Allocate array of CELL per each array (row)
    CELL** field = (CELL**) malloc(nrows*sizeof(CELL*));
    for (int i = 0; i < nrows; ++i)
        field[i] = (CELL*) malloc(ncols*sizeof(CELL));
    
    return (field);
}

void zerofill (CELL** field, int nrows, int ncols)
{
    // Just fill all with zeros
    CELL cell;
    cell.current_state = 0;
    cell.new_state = 0;
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            field[i][j] = cell;

}

