#include "stdio.h"

int n = 0, x[15001] = {0};

int bfind(int a){
    int l = 0, u = n-1, mid;
    while(l <= u){
        mid = (l+u)/2;
        if(a == x[mid]) return 1;
        else if(a > x[mid]) l = mid+1;
        else u = mid-1;
    }
    return 0;
}

int main(){
    int m = 0, cnt = 0, i = 0;
    int a = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    
    scanf("%d\n%d\n", &n, &x[0]);
    for(i = 1; i < n; ){
        scanf("%d\n", &x[i]);
        if(x[i] == x[i-1]) n--;
        else i++;
    }
    scanf("%d\n", &m);
    for(i = 0; i < m; i++){
        scanf("%d\n", &a);
        cnt += bfind(a);
    }

    printf("%d", cnt);

    return 0;
}