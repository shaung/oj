#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
	struct path{short hist[101]; double weight;};

	struct path p[501];
	int cur[501];
	int m = 0, n = 0;
	int i = 0, j = 0, k = 0, x = 0, inc = 0;
	double w = 0;
	char line[5501] = "";

	memset(p, 0, sizeof(p));
	memset(cur, 0, sizeof(cur));

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d\n", &m, &n);
	
	for(i = 0; i < m; i++){
		gets(line);
		for(k = 0, j = 0; j < n; j++){
			while(line[k] == 0x20)k++;
			for(cur[j] = 0; line[k] != 0x20 && line[k] != 0; k++){
				cur[j] = cur[j] * 10 + line[k] - 0x30;
			}
			p[j].weight += cur[j];
			p[j].hist[i] = j+1;
		}

		if(i == 0) continue;

		/* update p[k] for each j as vertex */
		for(j = 0; j < n; j++){
			for(w = p[j].weight, k = j-1; k >= 0; k--){
				w += cur[k];
				if(p[k].weight > w){
					p[k].weight = w;
					p[k].hist[i] = j+1;
					for(x = i-1; x >= 0; x--){
						p[k].hist[x] = p[j].hist[x];
					}
				}
			}
			for(w = p[j].weight, k = j+1; k < n; k++){
				w += cur[k];
				if(p[k].weight > w){
					p[k].weight = w;
					p[k].hist[i] = j+1;
					for(x = i-1; x >= 0; x--){
						p[k].hist[x] = p[j].hist[x];
					}
				}
			}
		}
	}

	for(w = p[0].weight, j = 0, i = 0; i < n; i++){
		if(w > p[i].weight){
			w = p[i].weight;
			j = i;
		}
	}

	for(i = 0; i < m - 1; i++){
		printf("%d ", p[j].hist[i]);
		if(p[j].hist[i] == p[j].hist[i+1]) continue;
		inc = (p[j].hist[i] < p[j].hist[i+1]) ? 1 : -1;
		for(k = p[j].hist[i] + inc; k != p[j].hist[i+1]+inc; k+=inc){
		    printf("%d ", k);
		}
	}
	printf("%d", p[j].hist[m-1]);

	return 0;
}
