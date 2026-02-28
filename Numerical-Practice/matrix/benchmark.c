#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "matrix.h"

double benchmark_matrix_multiply(int size);

int main(int argc, char *argv[]){
    // Check num of args
    if (argc < 3) {
        printf("Usage: %s <version> <notes>\n", argv[0]);
        printf("Example: %s baseline \"initial implementation\"\n", argv[0]);
        return 1;
    }

    // Get version and notes
    char *version = argv[1];
    char *notes = argv[2];

    // Check file status before printing head of results.csv
    struct stat buffer;
    if (stat("results/results.csv", &buffer) != 0 || buffer.st_size == 0) {
        printf("version,size,time_ms,gflops,notes\n");
    }

    // Set test sizes
    int sizes[] = {64, 128, 256, 512, 1024};

    // Start benchmarking
    for(int i=0; i<5; i++){
        double time_sec = benchmark_matrix_multiply(sizes[i]);
        double time_ms = time_sec * 1000;
        double g_flops = (2 * ((double)pow(sizes[i], 3))) / (time_sec * 1e9);
        printf("%s,%d,%.6f,%.2f,%s\n", version, sizes[i], time_ms, g_flops, notes);
    }

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
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    matrix_multiply(&mat_1, &mat_2, &result_mat);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    // Free all matrices
    free_matrix(&mat_1);
    free_matrix(&mat_2);
    free_matrix(&result_mat);

    return time_taken;
}