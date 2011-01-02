#include "stdio.h"

int main(int argc, char* argv[])
{
	char line[50] = "";
	short i = 0;
	unsigned long m = 0, n = 0, rslt = 0;
	unsigned char r = 0;

	gets(line);

	for(n = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
		n = n * 10 + (line[i] - 0x30);

	for(m = 0, i++; line[i] != 0x20 && line[i] != 0; i++)
		m = m * 10 + (line[i] - 0x30);

	if(m >= n)m = n;

	r = m & 0x01;
	rslt = (m >> 1) << 2;
	if(m >= n && r == 0)rslt -= 2;
	else if(m < n) {
		if(r == 1)rslt++;
		else rslt--;
	}

	printf("%lu\n", rslt);

	return 0;
}
