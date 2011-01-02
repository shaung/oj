#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int m = 0, n = 0;
    int tmp = 0;

    int minnum[50];
    int minprice[50];

    int price[2000];
    __int64 group[2000];
    int rslt[50];
    int rsltprice = 0, rsltcnt = 0;

    int i = 0, j = 0;
    char line[101];

    memset(minprice, 0, sizeof(minprice));
	
#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d\n", &m, &n);

    for(i = 0; i < m; i++){
        gets(line);
        for(group[i] = 0, j = 0; j < n; j++){
            if(line[2*j] > 0x30) group[i] |= (2 << j);
        }
    }

    for(i = 0; i < m; i++){
        scanf("%d", &price[i]);
        for(j = 0; j < n; j++){
            if((group[i] & (2 << j)) == (2 << j)){
                if(minprice[j] == 0 || minprice[j] > price[i]){
                    minprice[j] = price[i];
                    minnum[j] = i + 1;
                }
            }
        }
        gets(line);
    }

    for(i = 0; i < n; i++){
        if(minprice[i] == 0){
            printf("0");
            return 0;
        }
    }

    for(i = n - 1; i >= 0; i--){
        for(j = 0; j < i; j++){
            /* lexicographic order */
            if((minnum[j] > minnum[j+1]) &&
                ((minnum[j] < 10 && minnum[j+1] < 10) ||
                 (minnum[j] >= 10 && minnum[j+1] >= 10) ||
                 ((minnum[j] < 10 && minnum[j+1] >= 10) &&
                  (minnum[j] > minnum[j+1] / 10)))
               ){
                tmp = minnum[j+1];
                minnum[j+1] = minnum[j];
                minnum[j] = tmp;
            }
        }
        if(rsltcnt == 0){
            rslt[rsltcnt++] = minnum[i];
            rsltprice += minprice[i];
        }
        else if(rslt[rsltcnt - 1] != minnum[i]){
            rslt[rsltcnt++] = minnum[i];
            rsltprice += minprice[i];
        }
    }
    
    printf("%d\n", rsltprice);
    for(i = rsltcnt - 1; i >= 0; i--){
        printf("%d\n", rslt[i]);
    }

    return 0;
}

