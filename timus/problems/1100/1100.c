#include "stdio.h"
#include "string.h"

int id[150001];
int m[150001];

/* for this problem we need to use an in-place stable sorting algorithm */
int main(int argc, char* argv[])
{
    int n, i, j;
    char line[100];

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        gets(line);
        sscanf(line, "%d %d", &id[i], &m[i]);
    }

    for(i = 100; i >= 0; i--){
        for(j = 0; j < n; j++){
            if(m[j] == i)
                printf("%d %d\n", id[j], i);
        }
    }
    
    return 0;
}
