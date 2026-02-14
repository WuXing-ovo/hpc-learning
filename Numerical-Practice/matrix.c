#include <stdlib.h>
#include <stdio.h>

struct matrix{
    // Temperally use int, and it should be expanded when handle very large data.
    // All meta data of the matrix is here!
    int num_of_row;
    int num_of_col;
    double * ptr;
};

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
