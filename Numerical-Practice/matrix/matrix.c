#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

// Initialize error code
int matrix_errno = 0;

static inline int validate_index(const struct matrix *mat, int row, int col){
    // Check if the index is validated
    // It is based on 0 start rule and metadata check, which can not be used for matrix creating
    if(mat == NULL || mat->ptr == NULL){
        matrix_errno = MATRIX_ERR_INVALID_MATRIX;
        return 1;
    }
    if(row < 0 || row >= mat->num_of_row){
        matrix_errno = MATRIX_ERR_INVALID_ROW;
        return 1;
    }else if (col < 0 || col >= mat->num_of_col)
    {
        matrix_errno = MATRIX_ERR_INVALID_COL;
        return 1;
    }
    return 0;
}

static inline int validate_matrix(const struct matrix *mat){
    // Check if the matrix is valid
    // 0 for ok, 1 for not ok
    // For robust, it will also check the meta data
    if(mat == NULL || mat->ptr == NULL){
        // Check if the pointer is NULL
        matrix_errno = MATRIX_ERR_INVALID_MATRIX;
        return 1;
    }else if (mat->num_of_row <= 0)
    {
        // Check if the row number is valid
        matrix_errno = MATRIX_ERR_INVALID_ROW;
        return 1;
    }else if (mat->num_of_col <= 0)
    {
        // Check if the col number is valid
        matrix_errno = MATRIX_ERR_INVALID_COL;
        return 1;
    }
    return 0;
}

int create_matrix(int num_of_row, int num_of_col, struct matrix *mat){
    // Check matrix validity
    if(mat == NULL){
        matrix_errno = MATRIX_ERR_INVALID_MATRIX;
        return 1;
    }
    // Avoid unexpected inputs
    if(num_of_row <= 0){
        matrix_errno = MATRIX_ERR_INVALID_ROW;
        mat->ptr = NULL;
        return 1;
    }else if (num_of_col <= 0)
    {
        matrix_errno = MATRIX_ERR_INVALID_COL;
        mat->ptr = NULL;
        return 1;
    }
    // Initialize meta data of the matrix
    mat->num_of_row = num_of_row;
    mat->num_of_col = num_of_col;
    // Allocate memory
    size_t num_of_elements = (size_t)num_of_col * num_of_row;
    mat->ptr = (double *) malloc( num_of_elements * sizeof(double));
    // Check if the memory allocation was successful
    if(mat->ptr == NULL){
        matrix_errno = MATRIX_ERR_ALLOCATION;
        return 1;
    }
    return 0;
}

void free_matrix(struct matrix *mat){
    // Free the memory of a matrix.
    if(validate_matrix(mat)){
        return;
    }
    free(mat->ptr);
    mat->ptr = NULL;
}

double* get(const struct matrix *mat, int row, int col){
    // Use a pointer from user to return element.
    // Check if the row or the col is negative.
    // Check if the col and row exist.
    if(validate_index(mat, row, col)){
        return NULL;
    }
    // Return a pointer to point the address of an element.
    // Note: this implemention is designed for high performance
    // And, I choose to trust user, and to lower the friction
    // This function will return the memory address of the matrix to user
    // Make sure you and your implemention won't abuse that.
    // It might be changed in later versions when I realize that perfomance is not a threshold.
    size_t element_index = (size_t)row * mat->num_of_col + col;
    return (double *)(mat->ptr + (element_index));
}

int set(struct matrix *mat, int row, int col, double value){
    // Check if the row and col are valid
    if(validate_index(mat, row, col)){
        return 1;
    }
    // Repalce the value
    size_t element_index = (size_t)row * mat->num_of_col + col;
    mat->ptr[element_index] = value;
    return 0;
}

int print_matrix(const struct matrix *mat, int precision){
    // Check if the matrix is valid
    if(validate_matrix(mat)){
        return 1;
    }
    // By default (when user type negative numbers), precision will be set to 4
    if(precision < 0){
        precision = 4;
    }
    // Dynamic width
    int width = precision + 7;
    // Print the matrix
    for(int i=0; i<mat->num_of_row; i++){
        for(int j=0; j<mat->num_of_col; j++){
            size_t element_index = (size_t)i * mat->num_of_col + j;
            printf("%*.*f ", width, precision, mat->ptr[element_index]);
        }
        printf("\n");
    }
    return 0;
}

int fill(struct matrix *mat, double num){
    // Check if the matrix is valid
    if(validate_matrix(mat)){
        return 1;
    }
    // Computing num of elements outside for loop
    // Use size_t rather than int
    size_t num_of_elements = (size_t)mat->num_of_row * mat->num_of_col;
    // Replace all numbers with a specific number
    for(size_t i=0; i<num_of_elements; i++){
        mat->ptr[i] = num;
    }
    return 0;
}

int fill_0(struct matrix *mat){
    // Just use fill() with 0
    return fill(mat, 0);
}

int fill_1(struct matrix *mat){
    // Just use fill() with 1
    return fill(mat, 1);
}

int identity_matrix(struct matrix *mat){
    // Check if the matrix is valid
    if(validate_matrix(mat)){
        return 1;
    }
    // Check if the matrix is squared
    if(mat->num_of_col != mat->num_of_row){
        matrix_errno = MATRIX_ERR_NOT_SQUARED;
        return 1;
    }
    // Replace all elements with 0 firstly
    // then replace diagonal elements with 1
    // which can save lots of logical compare
    fill_0(mat);
    for(int j=0; j<mat->num_of_row; j++){
        size_t diag_index = (size_t)mat->num_of_col * j + j;
        mat->ptr[diag_index] = 1;
    }
    return 0;
}