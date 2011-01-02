#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
	short v[30001] = {0};
    int n = 0, i = 0, j = 0, k = 0, prev = 0, rslt = 0;
	int min = 0, max = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(min = 30000, max = 0, i = 0; i < n; i++){
        scanf("%d %d\n", &j, &k);
		if(j > v[k]) v[k] = j;
		if(min > k) min = k;
		if(max < k) max = k;
    }

	for(i = min; i <= max; i++){
		if(v[i] == 0) continue;
		if(v[i] > prev){
			prev = i;
			rslt++;
		}
	}

    printf("%d", rslt);

	return 0;
}