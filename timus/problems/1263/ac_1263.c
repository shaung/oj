#include "stdio.h"

int main(){
    int n = 0, m = 0, x[10000] = {0};
    int i = 0, a = 0;

#ifndef ONLINE_JUDGE
    freopen("p1263.in", "rt", stdin);
    freopen("p1263.out", "wt", stdout);
#endif

    scanf("%d %d", &n, &m);
    for(i = 0; i < m; i++){
        scanf("%d\n", &a);
        x[a-1]++;
    }

    for(i = 0; i < n; i++){
        printf("%.2f%%\n", (double)x[i]/(double)m * 100.0);
    }

    return 0;
}
