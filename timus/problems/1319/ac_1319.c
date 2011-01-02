#include "stdio.h"

int main(){
    int n = 0, i = 0, j = 0;
    int x[100] = {0};
    
    scanf("%d", &n);
    x[0] = 1;
    for(i = 1; i < n; i++)
        x[i] = x[i-1] + i;
    for(i = n; i > 0; i--){
        for(j = n-1; j >= 0; j--)
            printf("%d ", x[j]);
        for(j = 0; j < n-1; j++)
            x[j] = x[j+1] + 1;
        x[n-1] += i;
        printf("\n");
    }
    
    return 0;
}