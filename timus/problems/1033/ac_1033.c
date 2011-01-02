#include "stdio.h"

int m[35][35];
int n;

void paint(int, int);

int main(int argc, char* argv[])
{
    char line[35];
    int i = 0, j = 0, rslt = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        gets(line);
        for(j = 0; j < n; j++){
            m[i][j] = (line[j] == '.') ? 2 : 1;
        }
    }

    paint(0, 0);
    paint(n-1, n-1);

#ifndef ONLINE_JUDGE
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            printf("%d", m[i][j]);
        }
        printf("\n");
    }
#endif

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i == 0 && j == 0) continue;
            if(i == n-1 && j== n-1) continue;
            if(m[i][j] == 0) {
                /* north edge */
                if(j > 0 && i == 0) rslt++;
                /* east edge */
                if(j == n-1 && i < n-1) rslt++;
                /* south edge */
                if(j < n-1 && i == n-1) rslt++;
                /* west edge */
                if(j == 0 && i > 0) rslt++;
            }
            else if(m[i][j] == 1){
                /* north edge */
                if(i > 0)
                    if(m[i-1][j] == 0)rslt++;
                /* east edge */
                if(j < n-1)
                    if(m[i][j+1] == 0)rslt++;
                /* south edge */
                if(i < n-1)
                    if(m[i+1][j] == 0)rslt++;
                /* west edge */
                if(j > 0)
                    if(m[i][j-1] == 0) rslt++;
            }
        }
    }

    printf("%d", rslt * 9);

	return 0;
}

void paint(int x, int y){
    if(x < 0 || x > n-1 || y < 0 || y > n-1) return;
    if(m[x][y] == 1) return;
    if(m[x][y] == 2) m[x][y] = 0;
    if(x > 0 && x < n + 1 && y >= 0 && y < n)
        if(m[x-1][y] == 2) paint(x-1, y);
    if(x >= 0 && x < n && y > 0 && y < n + 1)
        if(m[x][y-1] == 2) paint(x, y-1);
    if(x >= 0 && x < n - 1 && y >= 0 && y < n)
        if(m[x+1][y] == 2) paint(x+1, y);
    if(x >= 0 && x < n && y >= 0 && y < n - 1)
        if(m[x][y+1] == 2) paint(x, y+1);
}