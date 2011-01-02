#include "stdio.h"
#include "string.h"

#define N_MAX   101
#define M_MAX   101

short v[N_MAX][M_MAX];

int main(int argc, char* argv[])
{
	int n = 0, m = 0, i = 0, j = 0, cnt = 1;

    memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d\n", &n, &m);

	if(n <= 0 || m <= 0){
		printf("-1");
		return 0;
	}

    cnt = 1;

	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			scanf("%d ", &v[i][j]);
		}
	}
	for(i = 1; i < n; i+=2){
		for(j = 1; j < m; j+=2){
			/* connected to the higher cell */
			if(v[i][j] == v[i+1][j] ||
               v[i][j+1] == v[i+1][j+1] ){
                v[i][j] = cnt;
                v[i][j+1] = cnt;
                cnt++;
                v[i+1][j] = cnt;
                v[i+1][j+1] = cnt;
                cnt++;
			}
            /* connected to the left cell */
            else {
                v[i][j] = cnt;
                v[i+1][j] = cnt;
                cnt++;
                v[i][j+1] = cnt;
                v[i+1][j+1] = cnt;
                cnt++;
			}
		}
	}

	for(i = 1; i <= n; i++){
		for(j = 1; j <= m; j++){
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}

	return 0;
}
