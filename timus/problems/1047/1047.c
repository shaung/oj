#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, i = 0;
    double xa = 0, xz = 0, c[3001] = {0.0};
    double d = 0.0, dsum = 0.0, xb = 0.0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n%lf\n%lf\n", &n, &xa, &xz);
    for(i = 1; i <= n; i++) scanf("%lf\n", &c[i]);

    d = 2*c[1] - xa;
    for(i = 2; i <= n; i++){
        dsum += (n+1-i)*c[i];
    }

    xb = (xz -(n*d + 2*dsum)) / (n + 1);

    printf("%.2f", xb);

	return 0;
}
