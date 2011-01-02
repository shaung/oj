#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int n = 0, i = 0, j = 0, len = 0;
    int q[10];

    memset(q, 0, sizeof(q));

    scanf("%d", &n);

    if(n == 0){
        printf("10");
        return 0;
    }

    while(n >= 10){
        for(i = 9; i >= 2; i--){
            j = n % i;
            if(j == 0){
                q[i]++;
                n /= i;
                break;
            }
        }
        if(j != 0){
            printf("-1");
            return 0;
        }
    }

    q[n]++;

    for(i = 0; i <= 9; i++)
        for(j = 0; j < q[i]; j++)
            printf("%d", i);
    
    return 0;
}
