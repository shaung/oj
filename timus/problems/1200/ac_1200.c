#include "stdio.h"
#include "math.h"

int main(int argc, char* argv[])
{
    double a = 0.0, b = 0.0, prof = 0.0, maxprof = 0.0;
    int n = 0, x = 0, y = 0, i = 0;
    double tx = 0.0, ty = 0.0;

    scanf("%lf %lf\n", &a, &b);
    scanf("%d", &n);

    if(a > 1.0 && b > 1.0){
        maxprof = 0.0;
        for(i = 0; i <= n; i++){
            prof = pow((2*i + a - b), 2) / 8.0 - (pow(i, 2) - b*i);
            tx = (double)(int)((2*i + a - b) / 4.0 + 0.5 - 1e-7);
            if(tx > i) tx = (double)i;
            if(tx < 0) tx = 0;
            ty = (double)(i - (int)tx);
            prof = a*tx + b*ty - (pow(tx, 2) + pow(ty, 2));
            if(prof > maxprof){
                maxprof = prof;
                x = tx;
                y = i - x;
            }
        }
    } else if(a > 1.0){
        /* should only consider the max (a*x - x^2) for x <= n */
        i = (a + 1) / 2;
        if(n > i){
            n = i;
        }
        for(i = n; i >= 0; i--){
            tx = (double)i;
            prof = a*tx - pow(tx, 2);
            if(prof > maxprof){
                maxprof = prof;
                x = i;
            }
        }
        y = 0;
    } else if(b > 1.0){
        /* should only consider the max (b*y - y^2) for y <= n */
        i = (b + 1) / 2;
        if(n > i){
            n = i;
        }
        for(i = 0; i <= n; i++){
            ty = (double)i;
            prof = b*ty - pow(ty, 2);
            if(prof > maxprof){
                maxprof = prof;
                y = i;
            }
        }
        x = 0;
    } else {
        maxprof = 0.0;
        x = 0;
        y = 0;
    }

    printf("%.2lf\n%d %d", maxprof, x, y);

    return 0;
}
