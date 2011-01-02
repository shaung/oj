#include "stdio.h"

int main(int argc, char* argv[])
{
	char line[3] = "";
	int i = 0;
	int n = 0;
	unsigned long rslt[46];

	gets(line);

	for(n = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
		n = n * 10 + (line[i] - 0x30);

	rslt[0] = 0;
	rslt[1] = 0;
	rslt[2] = 0;
	rslt[3] = 2;
	rslt[4] = 4;
	rslt[5] = 8;
	for(i = 6; i <= n; i++){
		rslt[i] = rslt[i - 1] * 2 - rslt[i - 3];
	}

	printf("%lu\n", rslt[n] + 2);

	return 0;
}
