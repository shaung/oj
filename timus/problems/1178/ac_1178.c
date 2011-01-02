#include "stdio.h"
void my_swap(int *a, int*b);
int main(int argc, char* argv[])
{
    int n = 0, i = 0, j = 0, tmp = 0;
    int x[10000] = {0}, y[10000] = {0}, rslt[10000] = {0};

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        scanf("%d %d\n", &x[i], &y[i]);
        rslt[i] = i + 1;
    }

    for(i = n-1; i > 0; i--){
        for(j = 0; j < i; j++){
            if(y[j] > y[j+1]){
                my_swap(&y[j], &y[j+1]);
                my_swap(&x[j], &x[j+1]);
                my_swap(&rslt[j], &rslt[j+1]);
            }
        }
    } 

    for(i = 0; i < n; i += 2){
        printf("%d %d\n", rslt[i], rslt[i+1]);
    }

	return 0;
}

void my_swap(int *a, int*b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}