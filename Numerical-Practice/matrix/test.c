#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

// Prototypes
void test_create_matrix();
void test_get_and_set();

int main(){
    test_create_matrix();
    printf("✅ test_create_matrix: pass!\n");

    test_get_and_set();
    printf("✅ test_get_and_set: pass!\n");
    
    return 0;
}

void test_create_matrix(){
    // Create matrix
    struct matrix mat;

    // Happy path
    int result = create_matrix(3, 3, &mat);
    assert(result == 0);
    assert(mat.num_of_row == 3);
    assert(mat.num_of_col == 3);
    assert(mat.ptr != NULL);

    free_matrix(&mat);
    assert(mat.ptr == NULL);

    // Reset error code
    matrix_errno = 0;
    // Error cases with NULL
    result = create_matrix(3, 3, NULL);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);

    // Reset error code
    matrix_errno = 0;
    // Error cases with wrong row number
    result = create_matrix(-1, 3, &mat);
    assert(result == 1);
    assert(mat.ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_ROW);

    // Reset error code
    matrix_errno =0;
    // Error cases with wrong column number
    result = create_matrix(3, -1, &mat);
    assert(result == 1);
    assert(mat.ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_COL);
}

void test_get_and_set(){
    // Happy path
    struct matrix mat;
    create_matrix(3, 3, &mat);
    int result = set(&mat, 1, 1, 5.2);
    assert(result == 0);
    assert(get(&mat, 1, 1) != NULL);
    assert(*get(&mat, 1, 1) == 5.2);
    free_matrix(&mat);

    // Error cases with wrong row number
    create_matrix(3, 3, &mat);

    // case: num_of_row < 0
    // set
    matrix_errno = 0;
    result = set(&mat, -1, 1, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_ROW);
    // get
    matrix_errno = 0;
    double* ptr = get(&mat, -1, 1);
    assert(ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_ROW);
    
    // case: num_of_col < 0
    // set
    matrix_errno = 0;
    result = set(&mat, 1, -1, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_COL);
    // get
    matrix_errno = 0;
    ptr = get(&mat, 1, -1);
    assert(ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_COL);

    // case: num_of_row out of boundary
    // set
    matrix_errno = 0;
    result = set(&mat, 10, 1, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_ROW);
    // get
    matrix_errno = 0;
    ptr = get(&mat, 10, 1);
    assert(ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_ROW);

    // case: num_of_col out of boundary
    // set
    matrix_errno = 0;
    result = set(&mat, 1, 10, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_COL);
    // get
    matrix_errno = 0;
    ptr = get(&mat, 1, 10);
    assert(ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_COL);

    // case: when mat.ptr is NULL
    // set
    matrix_errno = 0;
    result = set(NULL, 1, 1, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);
    // get
    matrix_errno = 0;
    ptr = get(NULL, 1, 1);
    assert(ptr == NULL);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);

    free_matrix(&mat);
}