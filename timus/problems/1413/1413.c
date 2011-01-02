#include "stdio.h"
#include "math.h"

#define sqrt2 (sqrt(2.0) / 2.0)

int main(int argc, char* argv[])
{
	char line[1000000] = "";
	int i = 0, j = 0;
	double x = 0.0, y = 0.0;
	int x1 = 0, xsqrt2 = 0, y1 = 0, ysqrt2 = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	gets(line);

	for(i = 0; line[i] != 0; i++){
		switch(line[i] - 0x30){
		case 0:
			x += x1;
			x += xsqrt2 * sqrt2;
			y += y1;
			y += ysqrt2 * sqrt2;
			printf("%.10lf %.10lf", x, y);
			return 0;
			break;
		case 1:
			xsqrt2--;
			ysqrt2--;
			break;
		case 2:
			y1--;
			break;
		case 3:
			xsqrt2++;
			ysqrt2--;
			break;
		case 4:
			x1--;
			break;
		case 5:
			break;
		case 6:
			x1++;
			break;
		case 7:
			xsqrt2--;
			ysqrt2++;
			break;
		case 8:
			y1++;
			break;
		case 9:
			xsqrt2++;
			ysqrt2++;
			break;
		default:
			break;
		}
	}

	x += x1;
	x += xsqrt2 * sqrt2;
	y += y1;
	y += ysqrt2 * sqrt2;
	printf("%.10lf %.10lf", x, y);

	return 0;
}
