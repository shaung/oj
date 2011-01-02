#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
	char line[20] = "";
	int i = 0, j = 0, k = 0, cx = 0, cy = 0, gcx = 0, gcy = 0;
    int m = 0, n = 0, s = 0, d = 0;
	long maxdist = 0, dist[100][100];
    int group[100] = {0};
    int gcnt = 1;
    int tmp = 0;

    memset(dist, 0, sizeof(dist));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d %d\n", &m, &n, &s);

    for(k = 0; k < n; k++){
        gets(line);

        for(cx = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
            cx = cx * 10 + (line[i] - 0x30);
        while(line[i] == 0x20) i++;
        for(cy = 0; line[i] != 0x20 && line[i] != 0; i++)
            cy = cy * 10 + (line[i] - 0x30);
        while(line[i] == 0x20) i++;
        for(d = 0; line[i] != 0x20 && line[i] != 0; i++)
            d = d * 10 + (line[i] - 0x30);

        if(cx == cy || d >= s){
            /* cycle */
            printf("YES");
            return 0;
        }

        if(cx > cy){
            tmp = cy;
            cy = cx;
            cx = tmp;
        }

        gcx = group[cx-1];
        gcy = group[cy-1];

        dist[cx-1][cy-1] = d;
        dist[cy-1][cx-1] = dist[cx-1][cy-1];

        /* both new comers */
        if(gcx == 0 && gcy == 0){
            /* new group */
            group[cx-1] = gcnt++;
            group[cy-1] = group[cx-1];
        }
        /* both alreday seen */
        else if(gcx != 0 && gcy != 0){
            /* the same group, cycle */
            if(gcx == gcy){
                printf("YES");
                return 0;
            }
            /* different groups */
            for(i = 0; i < m; i++){
                if(i == cx-1) continue; /* emit self-weight */
                /* for each in group-cx */
                /* recalculate distance for cy-1 and each item in group-cx*/
                /* just sum dist[i][cx-1] and dist[cx-1][cy-1] */
                if(group[i] == gcx){
                    dist[i][cy-1] = dist[i][cx-1] + d;
                    dist[cy-1][i] = dist[i][cy-1];
                }
            }
            /* move group-cy to group-cx */
            for(j = 0; j < m; j++){
                /* for each in group-cy */
                if(group[j] != gcy) continue;
                /* recalculate distance for group cy-1*/
                /* there could not be relations between them so just set it */
                for(i = 0; i < m; i++){
                    if(group[i] == gcx){
                        dist[i][j] = dist[j][cy-1] + dist[i][cy-1];
                        dist[j][i] = dist[i][j];
                    }
                }
                group[j] = gcnt;
            }
            /* move group-cy to group-cx */
            for(i = 0; i < m; i++){
                if(group[i] == gcnt) group[i] = gcx;
            }
        }
        else if(gcx != 0 && gcy == 0){
            /* cy is new to group cx */
            /* so we need to recalculate dist[cy-1][i(group[cx-1])] */
            group[cy-1] = gcx;
            for(i = 0; i < m; i++){
                if(i == cx-1 || i == cy-1) continue;
                /* recalculate distance for group-cx and cy the newbee*/
                if(group[i] == gcx){
                    dist[i][cy-1] = dist[i][cx-1] + d;
                    dist[cy-1][i] = dist[i][cy-1];
                }
            }
        }
        else if(gcx == 0 && gcy != 0){
            /* cx is new to group cy */
            /* so we need to recalculate dist[cx-1][i(group[cy-1])] */
            group[cx-1] = gcy;
            for(i = 0; i < m; i++){
                if(i == cx-1 || i == cy-1) continue;
                /* recalculate distance for group cx-1*/
                if(group[i] == gcy){
                    dist[i][cx-1] = dist[i][cy-1] + d;
                    dist[cx-1][i] = dist[i][cx-1];
                }
            }
        }
    }

    /* calculate the maximum path as cycle not found */
    for(k = 1; k < gcnt; k++){
        maxdist = 0;
        for(i = 0; i < m; i++){
            if(group[i] != k) continue;
            for(j = 0; j < m; j++){
                if(i == j || group[j] != k) continue;
                if(maxdist < dist[i][j]) maxdist = dist[i][j];
            }
        }
        if(maxdist >= s){
            printf("YES");
            return 0;
        }
    }

    printf("NO");

	return 0;
}
