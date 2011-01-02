#include "stdio.h"

int main(int argc, char* argv[])
{
    char line[50] = "";
    short i = 0, j = 0, pos = 0, digit = 0, pos2 = 0,s = 0;

    line[0] = 0x30;
    gets(line+1);

    for(i = 1; line[i+1] != 0x20; i++);
    line[i+1] = 0x30;
    for(j = i+2; line[j+1] != 0; j++);

    /* assume b > a */
    pos = j; digit = i;pos2 = i;s = i+1;
    if(2*i > j - 1){
         pos = i;
         pos2 = j;
         s = 0;
         digit = j - i - 1;
    }

    while(pos >= s){
        if(digit-- > 0)
            line[pos] += line[pos2--] - 0x30;
        if(line[pos] >= 0x3A){
            line[pos] -= 0x0A;
            line[pos-1]++;
        }
        pos--;
    }
    line[pos2] = 0;

    if(line[s] == 0x30)s++;
    printf("%s\n", line + s);

	return 0;
}