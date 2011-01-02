#include "stdio.h"
#include "string.h"

#define INFINITE 1000000007

int dist[10001] = {0}, cost[10001] = {0};

void my_swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(int argc, char* argv[])
{
	int n = 0, l[3] = {0}, c[3] = {0}, start = 0, end = 0;
	int min = 0, d = 0, i = 0, j = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d %d %d %d %d\n", &l[0], &l[1], &l[2], &c[0], &c[1], &c[2]);
	scanf("%d\n%d %d\n", &n, &start, &end);
	start--; end--;
	if(start > end) my_swap(&start, &end);
	for(i = 1; i < n; i++)
		scanf("%d\n", &dist[i]);
	for(i = end; i > start; i--){
		cost[i] = INFINITE;
	}

	for(i = start + 1; i <= end; i++){
		for(j = i - 1; j >= start; j--){
			d = dist[i] - dist[j];
			min = INFINITE;
			if(d <= l[0]) min = c[0];
			else if(d <= l[1]) min = c[1];
			else if(d <= l[2]) min = c[2];
			else continue;
			if(min + cost[j] < cost[i]) cost[i] = min + cost[j];
		}
	}

	printf("%d", cost[end]);
	
	return 0;
}
