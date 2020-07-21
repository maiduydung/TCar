#include<stdio.h>

int main(int argc, char const *argv[]){
    int a = 0x55;
    int b = 0xaa;

    //check if bit 3 of a == 0
    if ((b & (0x01<<3)) == 0 )
        printf("pass\n");
    else
        printf("fail\n");
    
    return 0;
}