#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

struct matrix{
    // Temperally use int, and it should be expanded when handle very large data.
    // All meta data of the matrix is here!
    int num_of_row;
    int num_of_col;
    double * ptr;
};

int create_matrix(int num_of_row, int num_of_col, struct matrix *mat);

#endif