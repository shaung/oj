#include "stdio.h"
#include "string.h"

#define N_MAX 15001
#define P_MAX 164026
#define SQR_N 405

char p[P_MAX] = {1};
int index[N_MAX]= {0};
int main()
{
	int n = 0, i = 0, j = 0;
	memset(p, 1, sizeof(p));

	p[1] = 0;

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	for(i = 2; i <= SQR_N; i++){
		for(j = 2; i*j < P_MAX; j++){
			p[i*j] = 0;
		}
	}

	for(j = 0, i = 2; i < P_MAX; i++){
		if(p[i]) index[++j] = i;
	}

	for(i = 0; i < n; i++){
		scanf("%d\n", &j);
		printf("%d\n", index[j]);
	}

	return 0;
}
