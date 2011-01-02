#include "stdio.h"
#include "math.h"

int main(){
    int n = 0, i = 0, x = 0;
    
    scanf("%d", &n);

    for(i = (int)sqrt((double)(2*n)); i > 0; i--){
        x = n - i*(i-1)/2;
        if(x % i == 0){
            printf("%d %d", x/i, i);
            break;
        }
    }

    return 0;
}