#include "stdio.h"

int testbit(int, int);

int main(int argc, char* argv[])
{
	int n = 0, w[20], sum = 0;
	char line[200] = "";
	int max = 0, diff = 0, min = 0;
	int i = 0, j = 0, k = 0;

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	/* freopen("output.txt", "wt", stdout); */
#endif

	scanf("%d\n", &n);

	for(i = 0; i < n;){
		gets(line);
		j = 0;
		while(line[j] != 0 && i < n){
			while(line[j] == 0x20) j++;
			for(w[i] = 0; line[j] != 0x20 && line[j] != 0; j++){
				w[i] = w[i] * 10  + line[j] - 0x30;
			}
			sum += w[i++];
		}
		if(line[j] == 0 && line[j - 1] == 0x20) i--;
	}

#ifndef ONLINE_JUDGE
	for(i = 0; i < n; i++){
		printf("w[%d]=%d\n", i , w[i]);
	}
#endif

	max = (2 << (n + 1)) - 1;
	min = sum;

	for(i = 1; i <= max; i++){
		diff = 0;
		for(j = 0; j < n; j++){
			if(testbit(i, j) == 1){
				diff += w[j];
			}
		}
		diff = sum - 2*diff;
		if(diff < 0) diff = 0 - diff;
		if(diff < min) min = diff;
		if(min == 0) break;
	}

	printf("%d", min);

	return 0;
}

int testbit(int num, int bit){
	int i = 0;
	
	if(bit < 2) i = bit;
	else i = 2 << bit;
	
	return ((num & i) == i) ? 1 : 0;
}
