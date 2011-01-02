#include "stdio.h"
#include "string.h"

struct vector{int value; short next; char p;};

struct vector v[10001];
int vcnt = 0;

int get_index(int value);
int find_root(int value, char *p);

int main(int argc, char* argv[])
{
    char line[26];
    int len = 0, cnt = 0;
    int i = 0, j = 0;
	int x, y, rx, ry;
	char p, px, py;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(scanf("%d\n", &len)){
        if(len == -1) break;

        scanf("%d\n", &cnt);

        memset(v, 0, sizeof(v));
        vcnt = 0;
        for(j = 0; j < cnt; j++){
            gets(line);

            for(x = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
                x = x * 10 + (line[i] - 0x30);

			x--;

            for(y = 0, i++; line[i] != 0x20 && line[i] != 0; i++)
                y = y * 10 + (line[i] - 0x30);

            p = (line[++i] == 'o') ? -1 : 1;

            if(x < 0 || y > len || x >= y)break;

			/* match */
			rx = find_root(x, &px);
			ry = find_root(y, &py);
			
			if(rx == ry){
				if(px*py != p) break;
			}
			else if(rx < ry){
				v[rx].next = ry;
				v[rx].p = px * py * p;
			} else {
				v[ry].next = rx;
				v[ry].p = px * py * p;
			}
        }

        printf("%d\n", j);

        while(++j < cnt){
            gets(line);
        }
    }
    return 0;
}

int get_index(int value){
	int i = 0;
	for(i = 0; i < vcnt; i++)
		if(v[i].value == value) return i;

	v[vcnt].value = value;
	v[vcnt].next = -1;
	v[vcnt].p = 0;
	return vcnt++;
}

int find_root(int value, char *p){
	int index = 0;
	index = get_index(value);

	*p = 1;
	while(v[index].next != -1){
		*p *= v[index].p;
		index = v[index].next;
	}
	
	return index;
}
