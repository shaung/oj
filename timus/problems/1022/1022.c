#include "stdio.h"
#include "string.h"

#define N_MAX 101

int main(int argc, char* argv[])
{
	int n = 0;
	char m[N_MAX][N_MAX]; /* x->y x is parents of y */
	char stack[N_MAX] = {0}, pos = 0;
	int i = 0, j = 0;

	memset(m, 0, sizeof(m));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);
	for(i = 1; i <= n; i++){
		while(scanf("%d ", &j) == 1){
			if(j == 0) break;
			m[i][j] = 1;
			m[0][j]++;
		}
	}

	for(i = 1; i <= n; i++){
		if(m[0][i] == 0){
			stack[pos++] = i;
			m[0][i]--;
			break;
		}
	}

	while(pos > 0){
		i = stack[--pos];
		printf("%d ", i);
		for(j = 1; j <= n; j++){
			if(m[j][0] == 1) continue;
			if(m[0][j] == m[i][j]){
				stack[pos++] = j;
				m[j][0] = 1;
			}
			if(m[i][j] == 1){
				m[0][j]--;
				m[i][j] = 0;
			}
		}
	}

	return 0;
}
