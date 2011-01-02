#include "stdio.h"

int divide(int n, int dir);

int main(int argc, char* argv[])
{
    double mp, mq;
    int y, p, q, i ,j;

    scanf("%lf %lf", &mp, &mq);

    p = (int)(mp * 100.0 + 1e-9);
    q = (int)(mq * 100.0 + 1e-9);

    for(y = 1; ; y++){
        i = divide(y * p, 1);
        j = divide(y * q, 2);
        if(j >= i) {
            break;
        }
    }

    printf("%d", y);

	return 0;
}

int divide(int n, int dir){
    int i = 0, m = n;
    for(i = 0; m >= 10000; i++) m -= 10000;
    if(dir == 1){
        if(m == 0) return i+2;
        else return i+1;
    }
    else {
        if(m == 0) return i-1;
        else return i;
    }
}
