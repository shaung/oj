#include "stdio.h"
#include "math.h"

#define PI acos(-1)

int main(int argc, char* argv[])
{
	int n = 0, i = 0;
	double r = 0.0, x[3] = {0.0}, y[3] = {0.0}, rslt = 0.0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif
	
	scanf("%d %lf\n", &n, &r);
	
	rslt = 2 * PI * r;
	
	scanf("%lf %lf\n", &x[0], &y[0]);
	x[2] = x[0]; y[2] = y[0];
	for(i = 1; i < n; i++){
		x[1] = x[2]; y[1] = y[2];
		scanf("%lf %lf\n", &x[2], &y[2]);
		rslt += sqrt(pow(y[2]-y[1], 2) + pow(x[2]-x[1], 2));
	}
	rslt += sqrt(pow(y[2]-y[0], 2) + pow(x[2]-x[0], 2));

	printf("%.2f", rslt);

	return 0;
}
