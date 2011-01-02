#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, inc = 0, step = 0;

    scanf("%d", &n);

    if(n == 1){
        printf("0\n");
        return 0;
    }
    
    for(n--, step = 30; step >= 0; step--){
        if(((1 << step) & n) == (1 << step)) break;
    }
    
    printf("%d\n", step+1);

    n++;
    while(n!=1){
        inc = n%2;
        n >>= 1;
        printf("%d ", n);
        n += inc;
    }
    
    return 0;
}
