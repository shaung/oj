#include "stdio.h"

int main(int argc, char* argv[])
{
	int n = 0, k = 0;
	int m = 0, rslt = 0;

	scanf("%d %d", &n, &k);

	m = n%k;
	if(n < k) rslt = 0;
	else if(m == 0) rslt = n*n/k;
	else if(2*m >= k) rslt = (n*n -(k-m)*(k-m))/k;
	else if(2*m <= k) rslt = (n*n -m*m)/k;

	printf("%d", rslt);

	return 0;
}
