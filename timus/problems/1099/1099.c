#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    short n = 0, degree[224] = {0}, i = 0, j = 0, min = 0, max = 0;
    char graph[224][224];
    short pair[111][2], cnt = 0;

    memset(graph, 0, sizeof(graph));

    scanf("%hd\n", &n);

    while(scanf("%hd %hd\n", &i, &j) == 2){
        if(graph[i][j] == 0){
            graph[i][j] = 1;
            graph[j][i] = 1;
            degree[i]++;
            degree[j]++;
        }
    }

    degree[0] = n;
    degree[n+1] = n;

    while(1){
        for(min = 0, i = 1; i <= n; i++){
            if(degree[i] > 0 && degree[i] < degree[min]) min = i;
        }
        if(min == 0) break;
        for(max = n+1, i = 1; i <= n; i++){
            if(graph[i][min] > 0 && degree[i] > 0 && degree[i] < degree[max]) max = i;
        }
        if(max == n+1) break;

        if(min < max){
            pair[cnt][0] = min;
            pair[cnt][1] = max;
        } else {
            pair[cnt][0] = max;
            pair[cnt][1] = min;
        }
        cnt++;
        for(i = 1; i <= n; i++){
            if(graph[i][min] > 0){
                degree[i]--;
                graph[i][min] = 0;
                graph[min][i] = 0;
            }
            if(graph[i][max] > 0){
                degree[i]--;
                graph[i][max] = 0;
                graph[max][i] = 0;
            }
        }
        degree[min] = 0;
        degree[max] = 0;
    }

    printf("%hd\n", (cnt << 1));
    for(i = 0; i < cnt; i++){
        printf("%hd %hd\n", pair[i][0], pair[i][1]);
    }

    return 0;
}
