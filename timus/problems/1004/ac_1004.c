#include "stdio.h"
#include "string.h"

#define MAX_LEN 50001
#define N_MAX   101

int n = 0, m = 0, cost[N_MAX][N_MAX], cost2[N_MAX][N_MAX];
char prev[N_MAX] = {0}, prev2[N_MAX] = {0}, checked[N_MAX] = {0};

int main(int argc, char* argv[])
{
    int i = 0, j = 0, k = 0, x = 0, y = 0, d = 0, d2 = 0, min = 0, u = 0, alt = 0, found = 0;

    memset(cost, 0, sizeof(cost));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(1){
        scanf("%d %d\n", &n, &m);
        if(n < 0) break;

        for(i = 0; i <= n; i++){
            for(j = 0; j <= n; j++){
                cost[i][j] = MAX_LEN;
            }
        }

        for(i = 0; i < m; i++){
            scanf("%d %d %d\n", &x, &y, &d);
            if(d < cost[x][y]){
                cost[x][y] = d;
                cost[y][x] = d;
            }
        }
        
        min = MAX_LEN;
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                if(i == j) continue;
                if(cost[i][j] >= MAX_LEN) continue;

                memset(prev2, 0, sizeof(prev2));
                memset(checked, 0, sizeof(checked));
                memcpy(cost2, cost, sizeof(cost));
                cost2[i][j] = MAX_LEN;
                cost2[j][i] = MAX_LEN;

                /* dijkstra */
                while(1){
                    for(u = 0, k = 1; k <= n; k++){
                        if(checked[k] != 1 && cost2[i][k] < cost2[i][u]){
                            u = k;
                        }
                    }
                    if(u == 0) break;
                    //if(u == j) break;
                    checked[u] = 1;

                    for(k = 1; k <= n; k++){
                        if(checked[k] != 0) continue;
                        alt = cost2[i][u] + cost2[u][k];
                        if(alt < cost2[i][k]){
                            cost2[i][k] = alt;
                            cost2[k][i] = alt;
                            prev2[k] = u;
                        }
                    }
                }

                if(cost[i][j] + cost2[i][j] <= min){
                    min = cost[i][j] + cost2[i][j];
                    x = i;
                    y = j;
                    memcpy(prev, prev2, sizeof(prev));
                }
            }
        }

        if(min >= MAX_LEN) printf("No solution.\n");
        else {
            printf("%d", x);
            while(y != 0){
                printf(" %d", y);
                y = prev[y];
            }
            printf("\n");
        }
    }
    
    return 0;
}
