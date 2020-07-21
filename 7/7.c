#include <stdio.h>

int main()
{
    FILE *fp = fopen("test.txt","r");
    if(!fp){
        fprintf(stderr, "ERROR: failed to open file\n");
        return 1;
    }

    char buf[128];
		
    while(fp){
        printf("%s", buf);
    }
    return 0;   
}