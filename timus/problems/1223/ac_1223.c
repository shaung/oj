#include "stdio.h"
#include "string.h"

short m[8][1000];

short calc(short, short);

int main(int argc, char* argv[])
{
	char line[10] = "";
	short i = 0;
	short n = 0 /* eggs */, f = 0 /* floors */;
	short rslt = 0;

	memset(m, 0, sizeof(m));

	while(gets(line)){
		if(line[0] == 0x30)break;

		for(n = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
			n = n * 10 + (line[i] - 0x30);
		if(n > 8) n = 8;

		for(f = 0, i++; line[i] != 0x20 && line[i] != 0; i++)
			f = f * 10 + (line[i] - 0x30);

		if(n == 1) rslt = f;
		else rslt = (m[n - 1][f] > 0) ? m[n - 1][f] : calc(n, f);

		printf("%d\n", rslt);
	}

	return 0;
}

short calc(short n, short f){

	short broken = 0, safe = 0, maxcost = 0, minstep = f;
	short i = 0;

	if(n == 1 || f < 3) return f; /* not more eggs */
	if(m[n - 1][f] > 0) return m[n - 1][f];

	for(i = 1; 2 * (i - 1) < f; i++){
		/* throw an egg from i+1's floor and see */
		broken = calc(n, f - 1 - i); /* broken */
		safe = calc(n - 1, i); /* not broken */

		maxcost = (broken > safe) ? broken : safe;
		maxcost++;
		if(minstep > maxcost) minstep = maxcost;
	}

	m[n - 1][f] = minstep;
	return minstep;
}