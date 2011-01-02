#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, rslt = 0;
    char sign = 1;

    scanf("%d", &n);

    if(n == 0) rslt = 1;
    else{
        sign = (n > 0) ? 1 : -1;
        n *= sign;
        rslt = (1+n)*(n/2);
   
        if(n%2 != 0) rslt += (1+n)/2;

        if(sign == -1){
            rslt--;
            rslt *= -1;
        }
    }
    
    printf("%d", rslt);

    return 0;
}
