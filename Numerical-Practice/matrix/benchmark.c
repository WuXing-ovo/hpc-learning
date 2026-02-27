#include <time.h>
#include <stdio.h>
#include <math.h>
#include "matrix.h"

double benchmark_matrix_multiply(int size);

int main(){
    // Calculate the time taken by matrix_multiply()
    int size = 1024;
    double time_taken = benchmark_matrix_multiply(size);
    double g_flops = (2 * ((double)pow(size, 3))) / (time_taken * 1e9);
    printf("matrix_multiply with size=%d took %f seconds to excute \n", size, time_taken);
    printf("matrix_multiply with size=%d took %f GFLOPS to excute \n", size, g_flops);
    return 0;
}

double benchmark_matrix_multiply(int size){
    // Create square matrices
    struct matrix mat_1;
    struct matrix mat_2;
    struct matrix result_mat;
    create_matrix(size, size, &mat_1);
    create_matrix(size, size, &mat_2);
    create_matrix(size, size, &result_mat);

    // Initialize input matrices
    fill_1(&mat_1);
    fill_1(&mat_2);

    // Multiply
    clock_t t;
    t = clock();
    matrix_multiply(&mat_1, &mat_2, &result_mat);
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC;

    // Free all matrices
    free_matrix(&mat_1);
    free_matrix(&mat_2);
    free_matrix(&result_mat);

    return time_taken;
}