#include<stdio.h>

int main(int argc, char const *argv[]){
    int a = 0x55;
    int b = 0xaa;

    //set bit
    b = b & ~(1<<3);
    printf("%x\n", b);
    if ((b & (0x01<<3)) == 0 )
        printf("pass\n");
    else
        printf("fail\n");
    
    return 0;
}