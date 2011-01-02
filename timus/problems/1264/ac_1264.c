#include "stdio.h"


int main(int argc, char* argv[])
{
    unsigned int m = 0, n = 0;
    
    scanf("%u %u", &n, &m);

    printf("%lu\n", (m+1)*n);

	return 0;
}
