#include "stdio.h"

int divide(char*, int);

int main(int argc, char* argv[])
{
    char line[52] = "0";
    int rslt = 0;

    gets(line + 1);

    rslt = divide(line, 7);

    printf("%d", rslt);

	return 0;
}

int divide(char* line, int n){
    int i = 0, mod = 0, cur = 0;

    for(i = 1; line[i] != 0; i++){
        cur = mod * 10 + line[i] - 0x30;
        mod = cur % n;
    }

    return mod;
}