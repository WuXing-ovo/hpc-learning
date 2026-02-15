#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

// Initialize error code
int matrix_errno = 0;

int create_matrix(int num_of_row, int num_of_col, struct matrix *mat){
    // Avoid unexpected inputs
    if(num_of_row <= 0){
        matrix_errno = MATRIX_ERR_INVALID_ROW;
        mat->ptr = NULL;
        return 1;
    }else if (num_of_col <= 0)
    {
        matrix_errno = MATRIX_ERR_INVALID_COL;
        mat->ptr = NULL;
        return 2;
    }
    // Initialize meta data of the matrix
    mat->num_of_row = num_of_row;
    mat->num_of_col = num_of_col;
    // Allocate memory
    mat->ptr = (double *) malloc((num_of_col * num_of_row) * sizeof(double));
    // Check if the memory allocation was successful
    if(mat->ptr == NULL){
        matrix_errno = MATRIX_ERR_ALLOCATION;
        return 3;
    }
    return 0;
}

void free_matrix(struct matrix *mat){
    // Free the memory of a matrix.
    free(mat->ptr);
    mat->ptr = NULL;
}

double* get(const struct matrix *mat, int row, int col){
    // Use a pointer from user to return element.
    // Check if the row or the col is negative.
    // Check if the col and row exist.
    if(row < 0 || row >= mat->num_of_row){
        matrix_errno = MATRIX_ERR_INVALID_ROW;
        return NULL;
    }else if(col < 0 || col >= mat->num_of_col){
        matrix_errno = MATRIX_ERR_INVALID_COL;
        return NULL;
    }
    // Return a pointer to point the address of an element.
    // Note: this implemention is designed for high performance
    // And, I choose to trust user, and to lower the friction
    // This function will return the memory address of the matrix to user
    // Make sure you and your implemention won't abuse that.
    // It might be changed in later versions when I realize that perfomance is not a threshold.
    return (double *)(mat->ptr + (row * mat->num_of_col + col));
}