#include "stdio.h"
#include "string.h"

void main(){
    char s[51] = "", max = 0;
    short r[27];
    int i = 0, j = 0;

    scanf("%s", s);

    memset(r, 0, sizeof(r));

    while(s[i] != 0x00){
        j = s[i] - 0x61;
        if(++r[j] > r[max]) max = j;
        i++;
    }

    printf("%c", max + 0x61);
}