#include "stdio.h"

int main(){
    int n = 0, x = 0, y = 0, cnt = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    
    scanf("%d\n", &n);
    while(n-- > 0){
        scanf("%c%d\n", &x, &y);
        x -= 0x60;
        cnt = 0;
        cnt += (x-1 > 0 && y-2 > 0);
        cnt += (x-1 > 0 && y+2 < 9);
        cnt += (x+1 < 9 && y-2 > 0);
        cnt += (x+1 < 9 && y+2 < 9);
        cnt += (x-2 > 0 && y-1 > 0);
        cnt += (x-2 > 0 && y+1 < 9);
        cnt += (x+2 < 9 && y-1 > 0);
        cnt += (x+2 < 9 && y+1 < 9);
        printf("%d\n", cnt);
    }

    return 0;
}