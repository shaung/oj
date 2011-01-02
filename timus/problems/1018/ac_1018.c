#include "stdio.h"
#include "string.h"

#define INFINITE 1000000000

struct node{char left, right, cnt; int weight, wsum;};
struct node v[100];

int best[100][100];

void calc_sum(char x);
char calc(char x, int n);

int main(int argc, char* argv[])
{
    int n = 0, q = 0, i = 0, j = 0, x = 0, y = 0, amount = 0;
    int m[100][100];
    char stack[100] = {0}, pos = 0, processed[100] = {0};

    memset(v, 0, sizeof(v));
    memset(best, 0, sizeof(best));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    for(i = 0; i < 100; i++){
        for(j = 0; j < 100; j++){
            m[i][j] = -1;
            best[i][j] = INFINITE;
        }
        best[i][0] = 0;
    }

    scanf("%d %d\n", &n, &q);

    for(i = 1; i < n; i++){
        scanf("%d %d %d\n", &x, &y, &amount);
        if(x > n || y > n) continue;
        x--; y--;
        m[x][y] = amount;
        m[y][x] = amount;
    }

    /* rebuild the binary tree from the undirected graph */
    stack[pos++] = 0;
    while(pos > 0){
        i = stack[--pos];
        processed[i] = 1;
        for(j = 0; j < n; j++){
            if(processed[j] == 1) continue;
            if(m[j][i] >= 0){
                m[j][i] = -1;
                v[j].weight = m[i][j];
                if(v[i].left == 0) v[i].left = j;
                else if(v[i].right == 0) v[i].right = j;
                else {printf("ERR"); return 0;}
                stack[pos++] = j;
            }
        }
    }

    /* dp */
    calc_sum(0);

    q = n - 1 - q;
    if(q < 0) q = 0;

    calc(0, q);
    printf("%d", v[0].wsum - best[0][q]);

	return 0;
}

void calc_sum(char x){
    v[x].cnt = 0;
    v[x].wsum = 0;
	if(v[x].left > 0){
		calc_sum(v[x].left);
	    v[x].cnt += 1 + v[v[x].left].cnt;
	    v[x].wsum += v[v[x].left].weight + v[v[x].left].wsum;
	}
    if(v[x].right > 0){
		calc_sum(v[x].right);
	    v[x].cnt += 1 + v[v[x].right].cnt;
	    v[x].wsum += v[v[x].right].weight + v[v[x].right].wsum;
	}
}

char calc(char x, int n){
    int i = 0, min = 0;

    if(best[x][n] != INFINITE) return 0;
    else if(v[x].cnt < n - 1) return -1;
	else if(v[x].cnt == n - 1){
		best[x][n] = v[x].wsum + v[x].weight;
		return 0;
	}
	else if(v[x].cnt == n){
		best[x][n] = v[x].wsum;
		return 0;
	}
    else if(v[x].left == 0 && v[x].right == 0){
        if(n > 1) return -1;
        best[x][n] = v[x].weight;
        return 0;
    }

    for(i = 0; i <= n; i++){
        min = 0;
        if(v[x].left > 0){
            if(0 != calc(v[x].left, i)) continue;
            min += best[v[x].left][i];
        }
        if(v[x].right > 0){
            if(0 != calc(v[x].right, n-i)) continue;
            min += best[v[x].right][n-i];
        }
        if(best[x][n] > min) best[x][n] = min;
    }

    if(best[x][n] == INFINITE) return -1;
    else return 0;
}