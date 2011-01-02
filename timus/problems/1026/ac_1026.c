#include "stdio.h"

void quick_sort(int *, int);
void my_swap(int *v, int a, int b);

int main(int argc, char* argv[])
{
    int n = 0, k = 0, v[100001] = {0};
    int i = 0, j = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);
    for(i = 0; i < n; i++) scanf("%d ", &v[i]);

    quick_sort(v, n);

    scanf("###\n%d\n", &k);
    for(i = 0; i < k; i++){
        scanf("%d ", &j);
        printf("%d\n", v[j-1]);
    }

	return 0;
}

void quick_sort(int *v, int n){
    int i = 0 , last = 0;
    
    if(n <= 1) return;
    
    i = (n >> 1) + 1;
    if(i >= n) i--;
    my_swap(v, 0, i);
    last = 0;
    for(i = 1; i < n; i++)
        if(v[i] < v[0])
            my_swap(v, ++last, i);
    my_swap(v, 0, last);

    quick_sort(v, last);
    quick_sort(v+last+1, n - last - 1);
}

void my_swap(int *v, int a, int b){
    int tmp = 0;
    tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}