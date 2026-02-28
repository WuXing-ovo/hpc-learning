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

static inline int dimension_check(const struct matrix *mat_1, const struct matrix *mat_2, const struct matrix *result){
    if(mat_1->num_of_row != mat_2->num_of_row || mat_1->num_of_col != mat_2->num_of_col || mat_1->num_of_row != result->num_of_row || mat_1->num_of_col != result->num_of_col){
        matrix_errno = MATRIX_ERR_DIMENSION_MISMATCH;
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

int matrix_add(struct matrix *mat_1, struct matrix *mat_2, struct matrix *result){
    // Check input matrices validity
    if(validate_matrix(mat_1) || validate_matrix(mat_2) || validate_matrix(result)){
        return 1;
    }
    // Check dimensions of matrices
    if(dimension_check(mat_1, mat_2, result)){
        return 1;
    }
    // Add element by element
    size_t num_of_element = (size_t)mat_1->num_of_row * mat_1->num_of_col;
    for(size_t i=0; i<num_of_element; i++){
        result->ptr[i] = mat_1->ptr[i] + mat_2->ptr[i];
    }
    return 0;
}

int matrix_subtract(struct matrix *mat_1, struct matrix *mat_2, struct matrix *result){
    // Check input matrices validity
    if(validate_matrix(mat_1) || validate_matrix(mat_2) || validate_matrix(result)){
        return 1;
    }
    // Check dimensions of matrices
    if(dimension_check(mat_1, mat_2, result)){
        return 1;
    }
    // Subtract element by element
    size_t num_of_element = (size_t)mat_1->num_of_row * mat_1->num_of_col;
    for(size_t i=0; i<num_of_element; i++){
        result->ptr[i] = mat_1->ptr[i] - mat_2->ptr[i];
    }
    return 0;
}

int matrix_scalar_multiply(struct matrix *mat, double scalar, struct matrix *result){
    // Check if matrices are valid
    if(validate_matrix(mat) || validate_matrix(result)){
        return 1;
    }
    // Check if dimensions match
    if(mat->num_of_row != result->num_of_row || mat->num_of_col != result->num_of_col){
        matrix_errno = MATRIX_ERR_DIMENSION_MISMATCH;
        return 1;
    }
    // Multiply each element by scalar
    size_t num_of_element = (size_t)mat->num_of_row * mat->num_of_col;
    for(size_t i=0; i<num_of_element; i++){
        result->ptr[i] = scalar * mat->ptr[i];
    }
    return 0;
}

int matrix_transpose(struct matrix *mat, struct matrix *result){
    // Check if matrices are valid
    if(validate_matrix(mat) || validate_matrix(result)){
        return 1;
    }
    // Check if dimensions match, mat should be m*n and result should be n*m
    if(result->num_of_col != mat->num_of_row || result->num_of_row != mat->num_of_col){
        matrix_errno = MATRIX_ERR_DIMENSION_MISMATCH;
        return 1;
    }
    // Transpose the matrix with two loops
    for(int i=0; i<mat->num_of_row; i++){
        for(int j=0; j<mat->num_of_col; j++){
            result->ptr[(size_t)j * result->num_of_col + i] = mat->ptr[(size_t)i * mat->num_of_col + j];
        }
    }
    return 0;
}

int matrix_multiply(struct matrix *mat_1, struct matrix *mat_2, struct matrix *result){
    // Check if matrices are valid
    if(validate_matrix(mat_1) || validate_matrix(mat_2) || validate_matrix(result)){
        return 1;
    }
    // Check if dimensions match, mat_1 is m*n, mat_2 is n*p, result is m*p
    if(mat_1->num_of_row != result->num_of_row || mat_2->num_of_col != result->num_of_col){
        matrix_errno = MATRIX_ERR_DIMENSION_MISMATCH;
        return 1;
    }

    // Set m, n, p
    int m = mat_1->num_of_row;
    int n = mat_1->num_of_col;
    int p = mat_2->num_of_col;

    // Initialize result matrix
    fill_0(result);

    // Loop by element of result
    // Optimized: from i-j-k to i-k-j
    for(int i=0; i<m; i++){
        for(int k=0; k<n; k++){
            double a_ik = mat_1->ptr[i * n + k];
            for(int j=0; j<result->num_of_col; j++){
                result->ptr[i * p + j] += a_ik * mat_2->ptr[k * p + j];
            }
        }
    }
    return 0;
}