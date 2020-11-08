#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ncurses.h>

// The cell struct. New type is customary to write it in caps.
typedef struct {
    int current_state;
    int new_state;
} CELL;

void new_state2current_state (CELL** field, int nrows, int ncols)
{
    /* Coder 2 */

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
    /* Coder 2 */

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
    if (j != ncols - 1) // East
        neighbours += field[i][j + 1].current_state;
    if (j != ncols-1 && i != nrows-1) // Southeast
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
    /* Coder 2 */

    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            compute_new_state (field, i, j, nrows, ncols);

}

void freemem (CELL** field, int nrows)
{
    /* Coder 2 */

    // Free the memory
    for (int i = 0; i < nrows; ++i)
        free(field[i]);
    free(field);
}

CELL** cellsmalloc (int nrows, int ncols)
{
    /* Coder 2 */

    // Allocate array of CELL per each array (row)
    CELL** field = (CELL**) malloc(nrows*sizeof(CELL*));
    for (int i = 0; i < nrows; ++i)
        field[i] = (CELL*) malloc(ncols*sizeof(CELL));
    
    return (field);
}

void zerofill (CELL** field, int nrows, int ncols)
{
    /* Coder 2 */

    // Just fill all with zeros
    CELL cell;
    cell.current_state = 0;
    cell.new_state = 0;
    for (int i = 0; i < nrows; ++i)
        for (int j = 0; j < ncols; ++j)
            field[i][j] = cell;

}

char** listfiles (int* nfiles)
{
    /* Coder 1 */

    /* This function takes an int pointer with no integer value on it and fills
     it with the number of .gol files in the ./../configs/ directory. It returns 
     a pointer of pointers that point to the dynamically allocated file names. */

    DIR* dir;
    struct dirent* entry;
    const char* ext;
    *nfiles = 0;

    // Go up one dir and try enter configs. Exit if it doesn't exist.
    dir = opendir ("./../configs/");
    if (dir == NULL)
    {
        fprintf(stderr, "Could not find ../configs/ \nexiting.\n");
        closedir(dir);
        exit(EXIT_FAILURE);
    }
    // Get number of files with .gol extension
    while ((entry = readdir (dir)) != NULL) 
    {
        // Check if file has .gol format
        ext = strrchr (entry->d_name, '.');
        if ( (ext != NULL) && (!strcmp (ext+1, "gol")) )
            *nfiles += 1;
    }
        
    // Allocate *nfiles pointers that will point to the .gol filenames
    char** filenames = (char**) malloc (*nfiles*sizeof(const char*));

    // Loop through each file in the directory 
    rewinddir(dir);
    int i = 0;
    while ((entry = readdir (dir)) != NULL) 
    {
        // Check if file has .gol format
        ext = strrchr (entry->d_name, '.');
        if ( (ext != NULL) && (!strcmp (ext+1, "gol")) )
        {
            filenames[i] = entry->d_name;
            i += 1;
        }
    }
    closedir(dir); 
    return filenames;
}

CELL** load_initconfig(char* file_path, int* initrows, int* initcols)
{
    /* Coder 1 */

	FILE *file_selected;
	file_selected = fopen(file_path, "r"); // Open the document in mode read
	int height = 0;                        // Variable that represents the height of the configuration
	int current_width = 0;                 // Variable that represents the width of the configuration
    int width = 0;
    int cols = 0;
	int k = 0;
	char character;

    // Check if the file exists
	if (file_selected == NULL)             
	{
        endwin();
		printf("The configuration selected doesn't exist\n");
        fclose(file_selected);
        exit(EXIT_FAILURE);
	}
	else 
    {
        // Count the number of lines of the configuration until the end of the file is reached
		while (!feof(file_selected)) 
        {     
			character = getc(file_selected); // Read the following character
			if (character == '0' || character == '1')
			{
                // Count the width of every row
				width++;
			} 
			else if (character == '\n')
			{
                if (k == 0)
                {
                    cols = width; // Store the width of the first row
                }
                else if (cols != width) // Compare the width of every row with the initial width to assure that are the same
                {
                    endwin();
                    printf("The configuration selected is incorrect. Number of columns is not the same for every row.\n");
                    fclose(file_selected);
                    exit(EXIT_FAILURE);
                }
				height++;
				width = 0; // Restart the width
				k++;
			}
		}
	}

    // Go back to the beginning of the file
	rewind(file_selected);

    // Create the grid that will contain the configuration
	CELL** grid_conf = cellsmalloc(height, cols); 
    // And fill it
	for (int i = 0; i < height; i++)
		for (int j = 0; j < cols; j++)
			fscanf(file_selected, "%1d", &grid_conf[i][j].current_state); // Save only the integer numbers in the grid


	// for (int i = 0; i < height; i++)
	//  {
	// 	 for (int j = 0; j < cols; j++)
	// 	 {
    //          printf("%d", grid_conf[i][j].current_state); // Print the values of check the configurations

	// 	 }
         
	//  }
    //  printf("\n %d %d \n", height, cols);
    
    *initrows = height;
    *initcols = cols;
    fclose(file_selected);
	return grid_conf;
}

void place_cells (CELL** canvas, CELL** cellinput, 
                  int canvas_rows, int canvas_cols, 
                  int cellin_rows, int cellin_cols)
{
    /* Coder 2 */

    // Place them in the center of the canvas.
    int startrow = canvas_rows/2 - cellin_rows/2;
    int startcol = canvas_cols/2 - cellin_cols/2;

    int k = 0, l = 0;
    for (int i = startrow; i < startrow + cellin_rows; i++)
    {
        for (int j = startcol; j < startcol + cellin_cols; j++)
        {
            canvas[i][j].current_state = cellinput[k][l].current_state;
            l += 1;
        }
        l = 0;
        k += 1;
    }
}