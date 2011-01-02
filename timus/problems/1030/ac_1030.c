#include "stdio.h"
#include "math.h"

#define PI acos(-1.0)
#define R  3437.5
#define RAD(x) ((x*PI)/(180.0*3600.0))

int main(int argc, char* argv[])
{
	char line[100] = "";
	int xd = 0, xm = 0, xs = 0, yd = 0, ym = 0, ys = 0;
	double x[2] = {0.0}, y[2] = {0.0};
	char dirx[2] = {0}, diry[2] = {0};
	double ra = 0.0, rb = 0.0, ro = 0.0, rslt = 0.0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	while(gets(line) != NULL){
		if(line[0] != 'M') continue;
		gets(line);
		gets(line);
		scanf("%d^%d'%d\" %c", &xd, &xm, &xs, &dirx[0]);
		gets(line);
		x[0] = xd*3600 + xm * 60 + xs;
		if(dirx[0] == 'S') x[0] *= -1;
		scanf("and %d^%d'%d\" %c", &yd, &ym, &ys, &diry[0]);
		gets(line);
		y[0] = yd*3600 + ym * 60 + ys;
		if(diry[0] == 'W') y[0] *= -1;
		gets(line);
		scanf("%d^%d'%d\" %c", &xd, &xm, &xs, &dirx[1]);
		gets(line);
		x[1] = xd*3600 + xm * 60 + xs;
		if(dirx[1] == 'S') x[1] *= -1;
		scanf("and %d^%d'%d\" %c", &yd, &ym, &ys, &diry[1]);
		gets(line);
		y[1] = yd*3600 + ym * 60 + ys;
		if(diry[1] == 'W') y[1] *= -1;

		rb = y[0] - y[1];

		ro = acos(sin(RAD(x[0]))*sin(RAD(x[1])) + cos(RAD(x[0]))*cos(RAD(x[1]))*cos(RAD(rb)));
		rslt = R*ro;
		printf("The distance to the iceberg: %.2lf miles.\n", rslt);
		if(rslt < 99.995) printf("DANGER!\n");
	}
	
	return 0;
}
