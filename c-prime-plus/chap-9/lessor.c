/* lesser.c -- finds the lesser of two evils */
#include <stdio.h>

int imin(int m, int n);

int main(){
    int evil1, evil2;
    printf("Enter a pair of integers (q to quit): \n");
    // Enter any character except integers is going to quit.
    while(scanf("%d %d", &evil1, &evil2) == 2){
        printf("The lessor of %d and %d is %d\n", evil1, evil2, imin(evil1, evil2));
        printf("Enter a pair of integers (q to quit): \n");

    }
}

int imin(int m, int n){
    int min;
    
    if(n<m){
        min = n;
    }else{
        min = m;
    }

    return min;
}