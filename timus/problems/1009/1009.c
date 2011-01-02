#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, k = 0, i = 0;
    __int64 v[2000] = {0};

    scanf("%d %d", &n, &k);

    v[1] = k - 1;
    v[2] = (k - 1) * (k - 1) + k - 1;
    for(i = 3; i <= n; i++){
        v[i] = (k-1) * (v[i-1] + v[i-2]);
    } 

    printf("%I64d", v[n]);

	return 0;
}
