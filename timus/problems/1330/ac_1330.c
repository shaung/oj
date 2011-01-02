#include "stdio.h"
#define N_MAX 10001

void my_swap(int *a, int *b){
	int tmp = *a; *a = *b; *b = tmp;
}

int main()
{
	int n = 0, m[N_MAX] = {0};
	int q = 0, i = 0, j = 0, k = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);
	for(i = 1; i <= n; i++){
		scanf("%d\n", &j);
		m[i] = m[i-1] + j;
	}

	scanf("%d\n", &q);
	while(q-- > 0){
		scanf("%d %d\n", &i, &j);
		if(i > j) my_swap(&i, &j);
		printf("%d\n", m[j] - m[i-1]);
	}

	return 0;
}
