#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int n = 0, m = 0;
char w[100001][16];
int freq[100001] = {0}, len[100001] = {0};
int v[15][100001];

void my_swap(int *v, int a, int b){
    int tmp = v[a]; v[a] = v[b]; v[b] = tmp;
}

void quicksort(int *v, int n, int x){
    int i = 0, last = 0, cmp = 0;
    if(n <= 1) return;
    my_swap(v, 0, n>>1);
    for(i = 1; i < n; i++){
		cmp = memcmp(w[v[i]], w[v[0]], x+1);
        if(cmp > 0){
            my_swap(v, ++last, i);
        } else if(cmp == 0 && freq[v[i]] > freq[v[0]]){
            my_swap(v, ++last, i);
		} else if(cmp == 0 && freq[v[i]] == freq[v[0]]){
			if(memcmp(w[v[i]]+x+1, w[v[0]]+x+1, 14-x) < 0)
	            my_swap(v, ++last, i);
		}
	}
    my_swap(v, 0, last);
    quicksort(v, last, x);
    quicksort(v + last + 1, n - last - 1, x);
}

int main(){
    int i = 0, j = 0, l = 0, cnt = 0, s[26] = {0}, next[26] = {0}, rslt = 0, cntr = 0;
    char k[16] = "";

    memset(w, 0, sizeof(w));
	memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
	
	/*
    freopen("input.txt", "wt", stdout);
	printf("100000\n");
	for(i = 0; i < 100000; i++){
		for(j = 15; j >=rand()%15; j--)
			printf("%c", 0x61 + rand()%26);
		printf(" %d\n", rand() % 1000000000);
	}
	printf("15000\n");
	for(i = 0 ; i < 15000; i++){
		for(j = 15; j >=rand()%15; j--)
			printf("%c", 0x61 + rand()%26);
		printf("\n");
	}
	*/

    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);
    for(i = 0; i < n; i++){
        v[0][i] = i;
        scanf("%s %d\n", w[i], &freq[i]);
		len[i] = 15;
		while(w[i][len[i]] == 0) len[i]--;
    }

	for(i = 0; i < 15; i++){
		for(j = 0; i > 0 && j < n; j++)
			v[i][j] = v[i-1][j];
	    quicksort(v[i], n, i);
	}

	for(i = 0; i < 26; i++){
		s[i] = n;
		next[i] = n;
	}
	s[*w[v[0][0]] - 0x61] = 0;
	for(i = 1; i < n; i++){
		if(*w[v[0][i]] != *w[v[0][i-1]]){
			s[*w[v[0][i]] - 0x61] = i;
			next[*w[v[0][i-1]] - 0x61] = i;
		}
	}
    
#ifndef ONLINE_JUDGE	
    for(i = 0; i < 15; i++){
	    for(j = 0; j < n; j++){
			printf("v[%d]: %s %d\n", i, w[v[i][j]], freq[v[i][j]]);
		}
		printf("\n");
    }
	printf("\n");
#endif

    scanf("%d\n", &m);

    while(m-- > 0){
        gets(k); l = strlen(k);
        cnt = 0;
        for(i = s[*k-0x61]; i < next[*k-0x61]; i++){
			//cntr++;
			rslt = memcmp(w[v[l-1][i]], k, l);
            if(rslt == 0){
				printf("%s\n", w[v[l-1][i]]);
				cnt++;
			}
			else if(rslt < 0) break;
            if(cnt >= 10) break;
        }
        if(m > 0) printf("\n");
    }
	//printf("cmp: %d\n", cntr);

    return 0;
}
