#include "stdio.h"

int main(int argc, char* argv[])
{
	int ix = 0, dx = 0, iy = 0, dy = 0;
	int z = 0, rslt = 0;

	scanf("%d %d %d %d", &ix, &dx, &iy, &dy);

	z = (iy - ix) / (dx + dy);

	if(ix >= iy) rslt = ix;
	else if(iy - dy*z > ix + dx*(z+1)) rslt = ix + dx*(z+1);
	else rslt = iy - dy*z;

	printf("%d", rslt);

	return 0;
}
