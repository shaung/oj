#include "stdio.h"

#define NODE_MAX 100001

int node[NODE_MAX] = {0};
int prev[NODE_MAX] = {0};
int canflyto[NODE_MAX] = {0};
int dist[NODE_MAX] = {0};
int path[NODE_MAX] = {0}, step = 0;

int main(int argc, char* argv[])
{
	int n = 0, i = 0, start = 0, end = 0;

#ifndef ONLINE_JUDGE
	/*
    freopen("input.txt", "wt", stdout);

	printf("%d\n", 99951);
	for(i = 6; i <= 10000; i++)
		printf("1 %d 2 %d 3 %d 4 %d 5 %d ", i, i, i, i, i);
	printf("1\n");
	*/
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	for(i = 1; i <= n; i++){
		scanf("%d[ \n]", &node[i]);
        if(prev[node[i]] != 0) canflyto[prev[node[i]]] = i;
        prev[node[i]] = i;
	}

    start = 1;
	end = n;

    for(i = start; i <= n; i++){
        dist[i] = NODE_MAX;
        prev[i] = i-1;
    }

	for(i = start; i <= n; i++){
        if(dist[i] > dist[i-1] + 1){
            dist[i] = dist[i-1] + 1;
            prev[i] = i-1;
        }
        if(canflyto[i] > 0){
            dist[canflyto[i]] = dist[i];
            prev[canflyto[i]] = i;
        }
    }

	for(i = n; i > start; i = prev[i]){
		if(path[step-1] != node[i])
			path[step++] = node[i];
	}
	if(path[step-1] != node[start])
		path[step] = node[start];
	else step--;

	for(i = step; i >= 0; i--)
		printf(" %d", path[i]);

	return 0;
}
