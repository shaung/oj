#include "stdio.h"

int main(int argc, char* argv[])
{
	char rslt[11] = "", c = 0;
	int n = 0, m = 0, i = 0, start = 0, s[2] = {0}, e[2] = {0};

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d\n", &n, &m);

	start = m%n;
	if(start + 9 < n){
		s[0] = start;
		e[0] = start + 9;
		s[1] = -1;
		e[1] = -1;
	} else {
		s[0] = start;
		e[0] = n - 1;
		s[1] = 0;
		e[1] = start + 9 - n;
	}

	for(i = 0; i < n; i++){
		scanf("%c\n", &c);
		if(i >= s[0] && i <= e[0]) rslt[i-start] = c;
		if(i >= s[1] && i <= e[1]) rslt[i-start+n] = c;
	}

	printf("%s", rslt);

	return 0;
}
