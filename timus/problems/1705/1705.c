#include "stdio.h"
#include "math.h"

int main(int argc, char* argv[])
{
	int t = 0;
	__int64 n = 0, i = 0, k = 0, now = 0, next = 0;

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &t);

	for(i = 0; i < t; i++){
		scanf("%I64d\n", &n);
		k = (int)sqrt((double)n);
		now = n/k;
		next = n/(k+1);
		while(now != next){
			now = next;
			k++;
			next = n/(k+1);
		}
		printf("%I64d\n", k);
	}

	return 0;
}
