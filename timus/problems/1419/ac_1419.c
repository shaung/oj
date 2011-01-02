#include "stdio.h"
#include "string.h"

#define N_MAX  100*100
#define IS_NUM(x) ((x >= 0x30) && (x <= 0x39))
#define IS_DIR(x) (x == '-' || x == '|' || x == '/' || x == '\\')

enum direction {d_rr = 1, d_rt = 2, d_tt = 4, d_lt = 8, d_ll = 16, d_lb = 32, d_bb = 64, d_br = 128};

char m[N_MAX] = ""; /* matrix */
unsigned char v[N_MAX] = ""; /* adj matrix */
short node[N_MAX] = {0}, rvs[N_MAX] = {0}, count = 0;
int w = 0, h = 0, len = 0;
short n[N_MAX] = {0}, cylic = 0;
short s[N_MAX] = {0}, sp = 0;
short b[N_MAX] = {0}, bp = 0;

int neighbor(int x, unsigned char dir){
	switch(v[x] & dir){
	case d_rr: return x + 2;
	case d_rt: return x - 2*w + 2;
	case d_tt: return x - 2*w;
	case d_lt: return x - 2*w - 2;
	case d_ll: return x - 2;
	case d_lb: return x + 2*w - 2;
	case d_bb: return x + 2*w;
	case d_br: return x + 2*w + 2;
	default: return -1;
	}
}

void dfs(int x){
	int i = 0;
	unsigned char j = 0;
	s[sp++] = x;
	n[x] = sp;
	if(n[x] > 1) b[bp++] = n[x];
	for(j = 0; j < 8; j++){
		i = neighbor(node[x], 1<<j);
		if(i < 0) continue;
		i = rvs[i];
		if(n[i] == 0){
			b[bp++] = n[x];
			dfs(i);
		} else {
			while(n[x] > 1 && n[i] < b[bp-2]) bp -= 2;
		}
	}
	if(n[x] == 1) n[s[--sp]] = cylic;
	else if(n[x] == b[bp-1]){
		bp -= 2; cylic++;
		while(n[x] <= sp)
			n[s[--sp]] = cylic;
	}
}

char chk_biconn(){
	int i = 0;
	cylic = count;

	dfs(0);

	if(cylic != count + 1) return 1;

	for(i = 0; i < count; i++){
		if(n[i] == 0) return 1;
	}

	return 0;
}

char chk_degree(){
	int i = 0;
	if(count != ((w+1)*(h+1) >> 2)) return 1;
	for(i = 0; i < count; i++){
		if(m[node[i]] != '3')
			return 1;
	}
	return 0;
}

void make_graph(){
	int i = 0, x = 0, y = 0;
	for(i = 0; i < len; i++){
		if(m[i] == '-'){
			x = i - 1; y = i + 1;
		} else if(m[i] == '|'){
			x = i - w; y = i + w;
		} else if(m[i] == '/'){
			x = i - w + 1; y = i + w - 1;
		} else if(m[i] == '\\'){
			x = i - w - 1; y = i + w + 1;
		} else {
			x = -1; y = -1;
		}

		if(x < 0 || y < 0 || x >= len || y >= len) continue;
		if(!IS_NUM(m[x]) || !(IS_NUM(m[y]))) continue;

		if(m[x] == '0'){rvs[x] = count;	node[count++] = x;}
		if(m[y] == '0'){rvs[y] = count;	node[count++] = y;}
		m[x]++; m[y]++;

		if(m[i] == '-'){
			v[x] |= d_rr; v[y] |= d_ll;
		} else if(m[i] == '|'){
			v[x] |= d_bb; v[y] |= d_tt;
		} else if(m[i] == '/'){
			v[x] |= d_lb; v[y] |= d_rt;
		} else if(m[i] == '\\'){
			v[x] |= d_br; v[y] |= d_lt;
		}
	}
}

int main(int argc, char* argv[])
{
	int i = 0;
	char err = 0;

#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
    //freopen("output.txt", "wt", stdout);
#endif

	scanf("%d %d\n", &w, &h);
	if(w%2 == 0 || h%2 == 0) err = 1;
	
	len = h*w;

	if(!err){
		for(i = 0; i < h; i++)
			gets(m + i*w);

		for(i = 0; i < len && !err; i++){
			if(m[i] == 'O')	m[i] = '0';
            else if(!IS_DIR(m[i]) && m[i] != 0 && m[i] != 0x20) err = 1;
		}
	}

	/* construct graph */
	if(!err) make_graph();

	/* 3-edges check */
	if(!err) err = chk_degree();

	/* biconnectivity */
	if(!err) err = chk_biconn();

	if(err) printf("Just a picture");
	else printf("Island world");

	return 0;
}
