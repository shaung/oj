#include "stdio.h"

__int64 dp[501][501];
__int64 calc(short start, short count);

int main(int argc, char* argv[])
{
    short n = 0, i = 0, j = 0;
    __int64 rslt = 0;

#ifndef ONLINE_JUDGE
    /* freopen("output.txt", "wt", stdout); */
#endif

    scanf("%d", &n);

	for(i = 0; i <= n; i++){
		for(j = 0; j <= n; j++)
			dp[i][j] = -1;
	}

    rslt = calc(0, n) - 1;

    printf("%I64d", rslt);

	return 0;
}

__int64 calc(short start, short count){
    short i = 0;
	__int64 ret = 0;

	if(dp[start][count] >= 0) return dp[start][count];
    if(count > start) ret = 1;
    for(i = start + 1; i < count - start; i++){
        ret += calc(i, count - i);
    }

    dp[start][count] = ret;
    return ret;
}
