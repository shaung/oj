#include "stdio.h"
#include "string.h"

#define INFINITE 127

unsigned int v[90][6];
char m[90][90], dist[91] = {0}, prev[90] = {0}, checked[90] = {0};
int n = 0;

int main(int argc, char* argv[])
{
	int i = 0, j = 0, k = 0, l = 0, ip[4] = {0}, sub[4] = {0}, start = 0, end = 0;
	char found = 0;

	memset(v, 0 , sizeof(v));
	memset(m, 0 , sizeof(m));
	memset(dist, INFINITE, sizeof(dist));
	memset(prev, -1, sizeof(prev));

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	for(i = 0; i < n; i++){
		scanf("%d\n", &v[i][0]);
		for(j = 1; j <= v[i][0]; j++){
			scanf("%d.%d.%d.%d %d.%d.%d.%d\n", ip+3, ip+2, ip+1, ip, sub+3, sub+2, sub+1, sub);
			for(k = 0; k < 4; k++) v[i][j] |= ((sub[k] & ip[k]) << (8*k));
		}
		for(j = 0; j < i; j++){
			found = 0;
			for(k = 1; k <= v[j][0] && found == 0; k++)
				for(l = 1; l <= v[i][0] && found == 0; l++)
					if(v[i][l] == v[j][k]) found = 1;
			if(found == 1){
				m[i][j] = 1; m[j][i] = 1;
			}
		}
	}

	scanf("%d %d", &start, &end); start--; end--;

	dist[end] = 0;
	while(1){
		for(i = n, j = 0; j < n; j++){
			if(checked[j] == 0 && dist[j] < dist[i]) i = j;
		}

		if(i == n) break;
		checked[i] = 1;
		if(i == start) break;

		for(j = 0; j < n; j++){
			if(checked[j] == 1 || m[i][j] == 0) continue;
			if(dist[j] > dist[i] + m[i][j]){
				dist[j] = dist[i] + m[i][j];
				prev[j] = i;
			}
		}
	}

	if(dist[start] == INFINITE) printf("No\n");
	else{
		printf("Yes\n");
		i = start;
		while(1){
			printf("%d ", i+1);
			if(i == end) break;
			i = prev[i];
		}
	}

	/*
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	*/

	return 0;
}
