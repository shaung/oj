#include "stdio.h"

int main(int argc, char* argv[])
{
	int n = 0, k = 0, x = 0, r = 0, rslt = 0;
	int i = 0;
	char line[50] = "";

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
#endif

	scanf("%d ", &n);
	gets(line);
	while(line[k] == '!') k++;

	if(k >= n){
		printf("%d", n);
		return 0;
	}

	x = n / k;
	r = n % k;
	if(r == 0){
		rslt = k;
		for(i = 0; i < x - 1; i++){
			if(n - i*k <= 0) break;
			rslt *= (n - i*k);
		}
	} else {
		rslt = r;
		for(i = 0; i < x; i++){
			if(n - i*k <= 0) break;
			rslt *= (n - i*k);
		}
	}

	printf("%d", rslt);

	return 0;
}
