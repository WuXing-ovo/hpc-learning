#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

void create_matrix(int num_of_row, int num_of_col, struct matrix *mat){
    // Avoid unexpected inputs
    if(num_of_row <= 0 || num_of_col <= 0){
        fprintf(stderr, "Error, num of row and num of col must be positive!\n");
        return;
    }
    // Initialize meta data of the matrix
    mat->num_of_row = num_of_row;
    mat->num_of_col = num_of_col;
    // Allocate memory
    mat->ptr = (double *) malloc((num_of_col * num_of_row) * sizeof(double));
}
