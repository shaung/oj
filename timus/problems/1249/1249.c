#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    struct tomb{int s, e;};

    struct tomb tnow[1501], tpre[1501];
    int m = 0, n = 0;
    int i = 0, j = 0, k = 0, status = 0 /* 0:waiting-for-one 1:counting-one */;
    int rslt = 0;
    int sznow = 0, szpre = 0;
    char line[3003] = "";

    memset(tpre, 0, sizeof(struct tomb));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d\n", &n, &m);

    for(i = 0; i < n; i++){
        gets(line);

        memset(tnow, 0, sizeof(struct tomb));
        sznow = 0;
        status = 0;

        for(j = 0; j < 2 * m; j+=2){
            if(line[j] == 0x30 && status == 1){
                tnow[sznow++].e = j - 2;
                status = 0;
            }
            else if(line[j] == 0x31){
                if(status == 0){
                    tnow[sznow].s = j;
                    status = 1;
                }
                if(line[j + 2] == 0){
                    tnow[sznow++].e = j;
                }
            }
        }

        for(j = 0; j < szpre;){
            rslt = -1;
            for(k = 0; k < sznow; k++){
                if(tnow[k].s == tpre[j].s && tnow[k].e == tpre[j].e){
                    rslt = 0;
                    break;
                }
                else if(tnow[k].s > tpre[j].e || tnow[k].e < tpre[j].s) continue;
                else {
                    rslt = 1;
                    break;
                }
            }

            if(rslt == -1){
                memcpy(tpre + j, tpre + szpre - 1, sizeof(struct tomb));
                szpre--;
                continue;
            }
            else if(rslt == 1){
                printf("No");
                return 0;
            } else j++;
        }

        memcpy(tpre, tnow, sznow * sizeof(struct tomb));
        szpre = sznow;
    }

    printf("Yes");

    return 0;
}
