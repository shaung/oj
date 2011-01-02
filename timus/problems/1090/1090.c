#include "stdio.h"

int main(int argc, char* argv[]){
    short n = 0, k = 0, i = 0, j = 0, l = 0, maxcnt = 0, maxi;
    short cnt[21] = {0}, tmp[10001] = {0};

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d\n", &n, &k);
    for(i = 0; i < k; i++){
        for(j = 0; j < n; j++){
            scanf("%d ", &tmp[j]);
        }
        for(j = 1; j < n; j++){
            for(l = 0; l < j; l++)
                if(tmp[l] > tmp[j]) cnt[i]++;
        }
        if(cnt[i] > maxcnt){
            maxcnt = cnt[i];
            maxi = i + 1;
        }
    }

    printf("%d", maxi);

    return 0;
}