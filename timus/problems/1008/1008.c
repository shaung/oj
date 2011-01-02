#include "stdio.h"
#include "string.h"

struct queqe{int x[100], y[100], pos, end;};

void in(struct queqe *q, int x, int y);
int out(struct queqe *q, int *x, int *y);

int main(int argc, char* argv[])
{
    char m[12][12];
    int n = 0, x = 0, y = 0, i = 0, j = 0;
    char line[6] = "";
    struct queqe q;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    memset(m, 0, sizeof(m));
    memset(&q, 0, sizeof(q));

    gets(line);
    if(line[1] == 0x20 || line[2] == 0x20){
        for(x = 0, i = 0; line[i] != 0x20; i++) x = x * 10 + line[i] - 0x30;
        for(y = 0, i++; line[i] != 0; i++) y = y * 10 + line[i] - 0x30;
        in(&q, x, y);
        while(gets(line)){
            if(out(&q, &x, &y) == -1) break;
            m[x][y] = 1;
            for(i = 0; line[i] != 0; i++){
                if(line[i] == 'R') in(&q, x+1, y);
                else if(line[i] == 'T') in(&q, x, y+1);
                else if(line[i] == 'L') in(&q, x-1, y);
                else if(line[i] == 'B') in(&q, x, y-1);
            }
        }

        printf("%d\n", q.pos);
        for(i = 1; i < 11; i++){
            for(j = 1; j < 11; j++){
                if(m[i][j] == 1) printf("%d %d\n", i, j);
            }
        }

    } else {
        for(n = 0, i = 0; line[i] != 0; i++) n = n * 10 + line[i] - 0x30;
        scanf("%d %d\n", &x, &y);
        in(&q, x, y);
        printf("%d %d\n", x, y);
        for(i = 0; i < n; i++){
            scanf("%d %d\n", &x, &y);
            m[x][y] = 1;
        }
        while(1){
            if(out(&q, &x, &y) == -1){
                printf(".");
                break;
            } else if(q.pos > 1){
                printf(",\n");
            }
            if(m[x+1][y] == 1){
                in(&q, x+1, y);
                m[x+1][y] = 2;
                printf("R");
            }
            if(m[x][y+1] == 1){
                in(&q, x, y+1);
                m[x][y+1] = 2;
                printf("T");
            }
            if(m[x-1][y] == 1){
                in(&q, x-1, y);
                m[x-1][y] = 2;
                printf("L");
            }
            if(m[x][y-1] == 1){
                in(&q, x, y-1);
                m[x][y-1] = 2;
                printf("B");
            }
        }
    }

	return 0;
}

void in(struct queqe *q, int x, int y){
    q->x[q->end] = x;
    q->y[q->end] = y;
    q->end++;
}

int out(struct queqe *q, int *x, int *y){
    if(q->pos >= q->end){
        return -1;
    }
    *x = q->x[q->pos];
    *y = q->y[q->pos];
    q->pos++;
    return 0;
}