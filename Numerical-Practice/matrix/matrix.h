#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

// Define error codes
#define MATRIX_OK 0
#define MATRIX_ERR_INVALID_ROW 1
#define MATRIX_ERR_INVALID_COL 2
#define MATRIX_ERR_ALLOCATION 3
#define MATRIX_ERR_INVALID_MATRIX 4
#define MATRIX_ERR_NOT_SQUARED 5
#define MATRIX_ERR_DIMENSION_MISMATCH 6

extern int matrix_errno;

struct matrix{
    // Temperally use int, and it should be expanded when handle very large data.
    // All meta data of the matrix is here!
    int num_of_row;
    int num_of_col;
    double * ptr;
};

int create_matrix(int num_of_row, int num_of_col, struct matrix *mat);

void free_matrix(struct matrix *mat);

double* get(const struct matrix *mat, int row, int col);

int set(struct matrix *mat, int row, int col, double value);

int print_matrix(const struct matrix *mat, int precision);

int fill(struct matrix *mat, double num);

int fill_0(struct matrix *mat);

int fill_1(struct matrix *mat);

int identity_matrix(struct matrix *mat);

int matrix_add(struct matrix *mat_1, struct matrix *mat_2, struct matrix *result);

#endif