#include "stdio.h"

int main()
{
	unsigned __int64 n = 0;
	scanf("%I64d", &n);
	printf("%I64d\n%I64d", n*n, n);
	return 0;
}
