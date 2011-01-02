#include "stdio.h"
#include "string.h"

int p[1000] = {0};
int power(int x, int n, int m){
	int i = 0;
	if(p[n] >= 0) return p[n];
	if(n == 2){
		p[n] = p[1]*p[1] % m;
	} else if (n == 3){
		p[n] = p[1] * power(x, 2, m) % m;
	} else if(n%2 == 0){
		power(x, n/2, m);
		p[n] = p[n/2]*p[n/2] % m;
	} else {
		power(x, n/2, m);
		power(x, n/2+1, m);
		p[n] = p[n/2]*p[n/2+1] % m;
	}
	return p[n];
}

int main(int argc, char* argv[])
{
	int n = 0, m = 0, y = 0;
	int i = 0, x = 0, cnt = 0;

	scanf("%d %d %d", &n, &m, &y);

	if(n == 1){
		if(y < m) printf("%d", y);
		else printf("-1");
 	    return 0;
	}

	for(x = 1; x < m; x++){
		memset(p, -1, sizeof(p));
		p[1] = x;
		if(power(x, n, m) == y){
			printf("%d ", x);
			cnt++;
		}
	}

	if(cnt == 0) printf("-1");

	return 0;
}
