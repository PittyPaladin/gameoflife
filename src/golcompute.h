#ifndef GOLCOMPUTE_H
#define GOLCOMPUTE_H

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

char** listfiles (int* nfiles);

CELL** load_initconfig(char* file_path, int* initrows, int* initcols);

void place_cells (CELL** canvas, CELL** cellinput, int canvas_rows, int canvas_cols, int cellin_rows, int cellin_cols);

#endif