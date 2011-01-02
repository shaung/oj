#include "stdio.h"
#include "string.h"

short parent[25001];

short find_root(short x);

int main(int argc, char* argv[])
{
	short t = 0, n = 0, i = 0, x = 0, y = 0, gx = 0, gy = 0;
	char failed = 0, nconfess = 0;

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &t);
	for(i = 0; i < t; i++){
		scanf("%d\n", &n);

		memset(parent, 0, sizeof(parent));
		failed = 0;
		nconfess = 0;
		for(x = 1; x <= n; x++){
			scanf("%d ", &y);
			if(failed == 1) continue;
			if(y == 0){
				if(++nconfess > 1) failed = 1;
				continue;
			}
			gx = find_root(x);
			gy = find_root(y);
			if(gx == 0 && gy == 0){
				parent[x] = x;
				parent[y] = x;
			}
			else if(gx != 0 && gy != 0){
				if(gx == gy) failed = 1;
				else parent[gy] = gx;
			}
			else if(gx == 0) parent[x] = gy;
			else if(gy == 0) parent[y] = gx;
		}
		if(failed == 0 && nconfess == 1) printf("YES\n");
		else printf("NO\n");
	}

	return 0;
}

short find_root(short x){
	if(parent[x] == x) return x;
	else parent[x] = find_root(parent[x]);
	return parent[x];
}