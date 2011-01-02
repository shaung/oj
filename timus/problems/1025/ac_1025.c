#include "stdio.h"

int main(int argc, char* argv[])
{
    int k = 0, n[101] = {0}, rslt = 0;
    int i = 0, j = 0, tmp = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &k);

    for(i = 0; i < k; i++) scanf("%d ", &n[i]);

    for(i = k - 1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(n[j] > n[j+1]){
                tmp = n[j];
                n[j] = n[j+1];
                n[j+1] = tmp;
            }
        }
    }

    j = (k >> 1) + 1;

    for(i = 0; i < j; i++){
        rslt += ((n[i] >> 1) + 1);
    }

    printf("%d", rslt);

    return 0;
}
