#include "stdio.h"
#include "string.h"

#define N_MAX 100001

void make_tree(int);
int calc(int, int);

struct node{ int next, level; char dir;};
struct node v[N_MAX];
char line[N_MAX] = "";
int w = 0, h = 0, n = 0;

int main(int argc, char* argv[])
{
	int q = 0, i = 0, j = 0, pos = 0, root = 0, x = 0, y = 0, a = 0, b = 0;

	memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d\n", &h, &w);
	n = w * h;
	while(pos < n){
		gets(line + pos);
		pos += w;
	}

#ifndef ONLINE_JUDGE
	for(i = 0; i < n; i++){
		if(line[i] == '.') printf("..");
		else printf("%2d", i);
		if((i+1)%w == 0) printf("\n");
	}
#endif

	while(1){
		for(root = 0; root < n && line[root] == '.'; root++);
		if(root == n) break;
		v[root].next = root;
		v[root].dir = 0;
		v[root].level = 0;
		make_tree(root);
	}

	scanf("%d\n", &q);

	for(i = 0; i < q; i++){
		scanf("%d %d ", &x, &y);
		a = (x-1) * w + y-1;
		scanf("%d %d ", &x, &y);
		b = (x-1) * w + y-1;
		printf("%d\n", calc(a, b));
	}

	return 0;
}

void make_tree(int cur){
	int i = 0, j = 0;
	
	line[cur] = '.';

	for(j = 0; j < 4; j++){
		if(j == 0) i = cur - w;
		else if(j == 1) i = (cur%w == 0) ? -1 : (cur - 1);
		else if(j == 2) i = cur + w;
		else if(j == 3) i = ((cur+1)%w == 0) ? -1 : (cur + 1);

		if(i < 0 || i >= n) continue;
		if(line[i] == '.') continue;

		/* v[i].dir = (j ^ 1) + 1; */
		if(j%2 == 0) v[i].dir = 2;
		else v[i].dir = 1;

		if(v[i].dir != v[cur].dir){
			v[i].next = cur;
			v[i].level = v[cur].level + 1;
		} else {
			v[i].next = v[cur].next;
			v[i].level = v[cur].level;
		}
		make_tree(i);
	}
}

int calc(int a, int b){
	int rslt = 0;

	/* if levels are the same, distances from each node to common parents are equal */
	/* if levels differ by 1, they may coincide */
	/* if a.level = b.level + 1, check a.next = b */
	/* if b.level = a.level + 1, check b.next = a */
	/* rslt[a..b] = nodes between a and b (not included) */

#ifndef ONLINE_JUDGE
	printf("--%d---%d--------\n", a, b);
#endif

	/* so first check if nodes coincide */
	if(v[a].next == b || v[b].next == a) return 0;
	if(v[a].next == v[b].next) return (((v[a].dir & v[b].dir) == 0) ? 1 : 0);

	while(v[a].level > v[b].level){
#ifndef ONLINE_JUDGE
		printf(" a = %d, b = %d, rslt = %d\n", a, b, rslt);
#endif
		a = v[a].next;
		rslt++;
		if(v[a].next == b) return rslt + ((v[b].next == b) ? 0 : 1);
	}
	while(v[b].level > v[a].level){
#ifndef ONLINE_JUDGE
		printf(" a = %d, b = %d, rslt = %d\n", a, b, rslt);
#endif
		b = v[b].next;
		rslt++;
		if(v[b].next == a) return rslt + ((v[a].next == a) ? 0 : 1);
	}
	rslt++;
	while(v[a].next != v[b].next){
#ifndef ONLINE_JUDGE
		printf(" a = %d, b = %d, rslt = %d\n", a, b, rslt);
#endif
		rslt +=2;
		a = v[a].next;
		b = v[b].next;
	}
	rslt += (((v[a].dir & v[b].dir) == 0) ? 1 : 0);
	if(rslt > 1) rslt--;
	return rslt;
}