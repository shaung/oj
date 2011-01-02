#include "stdio.h"

int main(int argc, char* argv[])
{
    short n = 0, i = 0, j = 0, k = 0, x = 0;
    int m[100][100], rslt[10000] = {0};

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(j = 0; j < n; j++){
        for(i = 0; i <= j; i++){
            m[i][j-i] = x++;
        }
    }
    for(j = n+1; j < 2*n; j++){
        for(i = j-n; i < n; i++){
            m[i][j-i-1] = x++;
        }
    }

    for(j = 0; j < n; j++){
        for(i = 0; i < n; i++){
            scanf("%d ", &rslt[m[i][j]]);
        }
    }

    for(i = 0; i < x; i++){
        printf(" %d", rslt[i]);
    }

    return 0;
}
