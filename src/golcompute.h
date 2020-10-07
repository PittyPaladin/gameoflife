typedef struct {
    int current_state;
    int new_state;
} CELL;

void new_state2current_state (CELL** field, int nrows, int ncols);

void compute_new_state (CELL** field, int i, int j, int nrows, int ncols);

void next_generation (CELL** field, int nrows, int ncols);

void freemem (CELL** field, int nrows);

CELL** cellsmalloc (int nrows, int ncols);

void zerofill (CELL** field, int nrows, int ncols);