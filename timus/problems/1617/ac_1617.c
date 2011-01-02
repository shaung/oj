#include "stdio.h"

int main(int argc, char* argv[])
{
    short cnt[101] = {0};
    short n = 0, i = 0, x = 0, rslt = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        scanf("%d", &x);
        cnt[x-600]++;
    }

    for(i = 0; i < 101; i++){
        rslt += (cnt[i] >> 2);
    }

    printf("%d", rslt);

	return 0;
}
