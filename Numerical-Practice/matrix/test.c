#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"

// Prototypes
void test_create_matrix();
void test_get_and_set();
void test_fills();
void test_identity();
void test_matrix_add();

int main(){
    test_create_matrix();
    printf("✅ test_create_matrix: pass!\n");

    test_get_and_set();
    printf("✅ test_get_and_set: pass!\n");

    test_fills();
    printf("✅ test_fills: pass!\n");
    
    test_identity();
    printf("✅ test_indentity: pass!\n");

    test_matrix_add();
    printf("✅ test_matrix_add: pass!\n");

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

void test_fills(){
    struct matrix mat;
    create_matrix(3, 3, &mat);

    // Test fill() with 5.2
    matrix_errno = 0;
    int result = fill(&mat, 5.2);
    assert(result == 0);
    size_t num_of_elements = (size_t)mat.num_of_col * mat.num_of_row;
    for(size_t i=0; i<num_of_elements; i++){
        assert(mat.ptr[i] == 5.2);
    }
    // Test fill() with NULL
    matrix_errno = 0;
    result = fill(NULL, 5.2);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);

    // Test fill_0()
    matrix_errno = 0;
    result = fill_0(&mat);
    assert(result == 0);
    num_of_elements = (size_t)mat.num_of_col * mat.num_of_row;
    for(size_t i=0; i<num_of_elements; i++){
        assert(mat.ptr[i] == 0);
    }
    // Test fill_0() with NULL
    matrix_errno = 0;
    result = fill_0(NULL);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);

    // Test fill_1()
    matrix_errno = 0;
    result = fill_1(&mat);
    assert(result == 0);
    num_of_elements = (size_t)mat.num_of_row * mat.num_of_col;
    for(size_t i=0; i<num_of_elements; i++){
        assert(mat.ptr[i] == 1);
    }
    // Test fill_1() with NULL
    matrix_errno = 0;
    result = fill_1(NULL);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);

    free_matrix(&mat);
}

void test_identity(){
    struct matrix mat;
    // Happy path, when input matrix is squared
    create_matrix(3, 3, &mat);
    int result = identity_matrix(&mat);
    assert(result == 0);
    for(size_t i=0; i<mat.num_of_row; i++){
        for(size_t j=0; j<mat.num_of_col; j++){
            if(i == j){
                assert(mat.ptr[(size_t)i * mat.num_of_col + j] == 1);
                continue;
            }
            assert(mat.ptr[(size_t)i * mat.num_of_col + j] == 0);
        }
    }
    free_matrix(&mat);

    // When input matrix is not squared
    create_matrix(1, 3, &mat);
    result = identity_matrix(&mat);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_NOT_SQUARED);
    assert(mat.ptr != NULL);

    // When input pointer is NULL
    result = identity_matrix(NULL);
    assert(result == 1);

    free_matrix(&mat);
}

void test_matrix_add(){
    struct matrix mat_1;
    struct matrix mat_2;
    struct matrix result_mat;

    // Happy path
    create_matrix(3, 3, &mat_1);
    fill_1(&mat_1);
    create_matrix(3, 3, &mat_2);
    fill_1(&mat_2);
    create_matrix(3, 3, &result_mat);

    matrix_errno = 0;
    int result = matrix_add(&mat_1, &mat_2, &result_mat);
    assert(result == 0);
    size_t num_of_elements = (size_t)mat_1.num_of_row * mat_1.num_of_col;
    for(size_t i=0; i<num_of_elements; i++){
        assert(result_mat.ptr[i] == mat_1.ptr[i] + mat_2.ptr[i]);
    }

    // When pointers are NULL
    matrix_errno = 0;
    result = matrix_add(NULL, &mat_2, &result_mat);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);
    matrix_errno = 0;
    result = matrix_add(&mat_1, NULL, &result_mat);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);
    matrix_errno = 0;
    result = matrix_add(&mat_1, &mat_2, NULL);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);
    matrix_errno = 0;
    result = matrix_add(NULL, NULL, NULL);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_INVALID_MATRIX);
    
    // Free all matrices
    // To avoid unexpected changes
    free_matrix(&mat_1);
    free_matrix(&mat_2);
    free_matrix(&result_mat);
    // And recreate them
    create_matrix(3, 1, &mat_1);
    fill_1(&mat_1);
    create_matrix(3, 3, &mat_2);
    fill_1(&mat_2);
    create_matrix(3, 3, &result_mat);

    // Test invalid inputs: DIMENSION_MISMATCH
    matrix_errno = 0;
    result = matrix_add(&mat_1, &mat_2, &result_mat);
    assert(result == 1);
    assert(matrix_errno == MATRIX_ERR_DIMENSION_MISMATCH);

    free_matrix(&mat_1);
    free_matrix(&mat_2);
    free_matrix(&result_mat);
}