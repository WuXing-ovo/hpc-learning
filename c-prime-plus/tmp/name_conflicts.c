// To test if an identifier used as a formal parameter in a function prototype conflicts with variables in other scopes.
#include <stdio.h>

void show_n_char(int number, char ch);

int main(){
    float number = 10.0;
    show_n_char(20, '*');
    printf("\n");
    printf("%f\n", number);
}

void show_n_char(int num, char ch){
    for(int i=0; i<num; i++){
        printf("%c",ch);
    }
}