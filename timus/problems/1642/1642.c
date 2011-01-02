#include "stdio.h"

int main(){
    int n = 0, x = 0, l = -1001, r = 1001, m = 0;

    scanf("%d %d\n", &n, &x);

    while(n-- > 0){
        scanf("%d ", &m);
        if(m > 0 && m < r) r = m;
        else if(m < 0 && m > l) l = m;
    }
    
    /* left right */
    if(x > 0 && r > x) printf("%d %d", x, x - 2*l);
    else if(x < 0 && l < x) printf("%d %d", 2*r - x, -1*x);
    else printf("Impossible");
}