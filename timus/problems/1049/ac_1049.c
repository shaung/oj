#include "stdio.h"

short d[10001] = {0};

void calc(int x){
	int i = 0;
	if(d[x] == 0) return;

	/* find a*b=x until both a and b are prime numbers */
	for(i = 2; i*2 <= x; i++){
		if(x%i != 0) continue;
		d[i] += d[x]; d[x/i] += d[x];
		d[x] = 0;
		calc(i); calc(x/i);
		break;
	}
}

int main(int argc, char* argv[])
{
	int x = 0, i = 0, count = 0;

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif

	while(scanf("%d\n", &x) == 1)
		if(x != 1) d[x]++;

	for(count = 1, i = 10000; i >= 2; i--){
		if(d[i] > 0) calc(i);
		count *= (d[i] + 1);
	}

	printf("%d", count%10);

	return 0;
}
