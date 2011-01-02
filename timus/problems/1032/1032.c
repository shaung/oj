#include "stdio.h"
#include "string.h"

short m[10001] = {0}, sum[10001] = {0};

int main(int argc, char* argv[])
{
	int n = 0, i = 0, j = 0, x = 0, prev = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);
	sum[0] = 1;
	for(i = 1; i <= n; i++){
		scanf("%d\n", &m[i]);
		x = (m[i] + prev)%n;
		if(sum[x] == 0) sum[x] = i + 1;
		else{
			j = sum[x];
			break;
		}
		prev = x;
	}
	printf("%d\n", i - j + 1);
	for(; j <= i; j++){
		printf("%d\n", m[j]);
	}

	return 0;
}
