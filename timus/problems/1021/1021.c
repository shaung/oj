#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0;
    char x[75537] = {0}, *p = x + 42768, *q = p - 10000;
    int i = 0, j = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &n);
    for(i = 0; i < n; i++){
        scanf("%d\n", &j);
        *(p - j) = 1;
    }

    scanf("%d\n", &n);
    for(i = 0; i < n; i++){
        scanf("%d\n", &j);
        if(*(q + j) == 1){
            printf("YES");
            return 0;
        }
    }

    printf("NO");

	return 0;
}
