#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int y = 0, n = 0, q = 0, i = 0, j = 0, k = 0, cnt = 0;
    char line[201][39], current[39] = "", *cur = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    scanf("%d %d %d\n", &y, &n, &q);

    for(i = 0; i < n; i++){
        gets(line[cnt]);
        cur = line[cnt];
        for(j = 0; line[cnt][j] != 0; j++){
            current[j] = line[cnt][j] + ((cur[j] >= 0x41 && cur[j] <= 0x5A) ? 0x20 : 0);
        }
        if(line[cnt][j-2] == '#')j-=2;
        else j--;
        for(k = 0; k < cnt; k++){
            if(memcmp(line[k], current, j) == 0) break;
        }
        if(k == cnt) cnt++;
        if(cnt > q){
            printf("%s", line[cnt-1]);
            return 0;
        }
        for(j = 0; cur[j] != 0; j++)
            if(cur[j] >= 0x41 && cur[j] <= 0x5A)
                cur[j] += 0x20;
    }

	return 0;
}
