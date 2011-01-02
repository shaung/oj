#include "stdio.h"
#include "math.h"

int main(int argc, char* argv[])
{
    int n = 0, i = 0;
	__int64 s = 0;
    double x = 0.0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d", &n);

    /* f(n) = 1 + n*(n-1)/2 */
    for(i = 0; i < n; i++){
        scanf("%I64d\n", &s);
        x = sqrt((double)(8*s-7));
        if((x - (int)x) == 0.0 && (int)x%2 == 1)
            printf("1 ");
        else printf("0 ");
    }
    
    return 0;
}
