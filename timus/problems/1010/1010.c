#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, i = 0, rslt = 0;
    __int64 now = 0, prev = 0;
    unsigned __int64 x = 0, incline = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(x = 0, i = 0; i < n; i++){
        prev = now;
        scanf("%I64d\n", &now);
        incline = (now > prev) ? (now - prev) : (prev - now);
        if(i == 1){
            x = incline;
            rslt = 1;
            continue;
        }
        if(incline > x && i > 0){
            x = incline;
            rslt = i;
        }
    }

    printf("%d %d", rslt, rslt + 1);

	return 0;
}
