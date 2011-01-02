#include "stdio.h"

char x[1000000] = "", y[1000000] = "", rslt[1000001] = "";

void calc(char*, char*, char*, int);

int main(int argc, char* argv[])
{
	int n = 0;
	int i = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	for(i = 0; i < n; i++){
		scanf("%c %c\n", &x[i], &y[i]);
	}

	calc(rslt, x, y, n);
	
	printf("%s", rslt);

	return 0;
}

void calc(char *rslt, char *x, char *y, int n){
	int i  = 0, tmp = 0, addtive = 0;
	for(i = n - 1; i >= 0; i--){
		tmp = x[i] + y[i] - 0x60 + addtive;
		rslt[i] = (tmp % 10) + 0x30;
		addtive = tmp / 10;
	}
}
