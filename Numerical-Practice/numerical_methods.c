// Scientific computing exercises in C.
#include <stdio.h>
#include <math.h>

double dot_product(const double *a, const double *b, int size){
    // Computing the dot product between two vectors.
    double sum = 0.0;
    for(int i=0; i<size; i++){
        sum += (*(a+i) * *(b+i));
    }
    return sum;
}

double exp_x_taylor(double x){
    // Computing Taylor expansion of exp(x) with a specific tolerance of 1e-10.
    double sum = 1.0;
    double term = 1.0;
    for(int n=1; ;n++){
        term *= x / n;
        if(fabs(term) < 1e-10){
            break;
        }
        sum += term;
    }
    return sum;
}