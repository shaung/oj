#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, i = 0;

    scanf("%d", &n);

    printf("0\n");
    for(i = 1; i <= n; i++){
        printf("X\n*\n%d\n+\n", i);
    }

	return 0;
}
