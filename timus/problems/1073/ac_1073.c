#include "stdio.h"
#include "math.h"

#define INFINITE 1000000000

int best[60001] = {0};

void calc(int n){
	int i = 0, j = 0, m = 0;

	if(best[n] > 0) return;

	best[n] = INFINITE;
	m = (int)sqrt((double)n);
	for(i = m; i >= 2 && best[n] > 2; i--){
		j = i*i;
		if(best[n-j] == 0) calc(n - j);
		if(best[n] > 1 + best[n-j])
			best[n] = 1 + best[n-j];
	}
}

int main(int argc, char* argv[])
{
	unsigned int n = 0, m = 0, x = 0, i = 0;

	scanf("%d", &n);

	best[1] = 1; best[2] = 2; best[3] = 3;

	m = (int)sqrt((double)n);
	for(i = 2; i <= m; i++){
		for(x = i*i; x <= n; x *= x){
			if(best[x] == 1) break;
			else best[x] = 1;
		}
	}

	calc(n);

	printf("%d", best[n]);
	
	return 0;
}
