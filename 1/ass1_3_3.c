#include<stdio.h>

int main(int argc, char const *argv[]){
    int val = 0xffffffff;
    //clear bit 5 and 7
    val = val & ~(1<<5 | 1<<7);
    printf("%x\n", val);
    if( ( val & (1<<5 | 1<<7) ) == 0 )
        printf("pass\n");
    else
        printf("fail. %x\n", val);
    
    return 0;
}