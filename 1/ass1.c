#include<stdio.h>

int main(int argc, char const *argv[]){
    int a = 1;
    int b = 2;
    int *ptr_a, *ptr_b;
    
    printf("address a = %p, address b = %p\n", &a, &b);

    ptr_a = &a;
    ptr_b = &b;

    printf("a = %d, b = %d\n", *ptr_a, *ptr_b);

    return 0;
}