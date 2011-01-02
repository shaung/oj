#include "stdio.h"
#include "string.h"

#define N_MAX 10001
#define DIFF(X, Y)   m[v[X]] - m[v[Y]]

int m[N_MAX] = {0}, v[N_MAX] = {0};

void my_swap(int *v, int a, int b){
    int tmp = v[a]; v[a] = v[b]; v[b] = tmp;
}

void quicksort(int *v, int n){
    int i = 0, last = 0;
    if(n <= 1) return;
    my_swap(v, 0, n>>1);
    for(i = 1; i < n; i++){
        if(m[v[i]] < m[v[0]]) my_swap(v, ++last, i);
	}
    my_swap(v, 0, last);
    quicksort(v, last);
    quicksort(v + last + 1, n - last - 1);
}

void do_reform(int *n){
    int i = 0, last = 0;

    v[*n] = -2;
    for(i = *n - 1; i > 0; i--){
        if(m[v[i]] == m[v[i-1]]) v[i] = -1;
    }

    i = 0;
    while(v[++i] >= 0);
    last = i;
    if(v[i] != -2) while(v[++i] == -1);

    while(v[i] != -2){
        v[last] = v[i]; v[i] = -1;
        while(v[++i] == -1);
        while(v[++last] >= 0);
    }
    *n = last;
}

__int64 cntr = 0, cntr2 = 0;
int max[N_MAX] = {0};
int mlen = 0, mstart = 0, mstep = 0;

int find_next(int left, int right, int value){
	int mid = 0;

	if(value < 0 || left < 0 || left > right) return -1;
	if(m[v[left]] == value) return left;
	if(m[v[right]] == value) return right;

	while(left < right){
		cntr++;
		mid = (left+right)/2;
		if(m[v[mid]] == value) return mid;
		else if(m[v[mid]] > value) right = mid;
		else left = mid + 1;
	}
	return ((left == right && m[v[left]] == value) ? left : -1);
}

/*
   see through all the [i, i+1], [i, i+2], ...[i, i+n/2]
*/
void calc(int n, int inc){
    int i = 0, j = 0, k = 0, h = 0, s = 0, exp = 0, cnt = 0;

    for(i = 0; i+inc <= n; i+=((i == 0) ? inc : 1)){
		cntr2++;
		if(i/(inc+1) + (n-i+1)/ inc <= mlen) break;
        s = DIFF(i+inc, i);
        if(max[i] == s) continue;
        cnt = 1;

		k = i; h = i - inc;
		while(h >= 0){
			exp = m[v[k]] - s;
			if(m[v[0]] <= exp) h = find_next(0, h, exp);
			else break;
			if(h < 0) break;
			if(max[h] == s) break;
			cnt++; max[h] = s; k = h; h -= inc;
		}
		j = k;

		k = i + inc; h = k + inc;
		while(h <= n){
			exp = m[v[k]] + s;
			if(m[v[n]] >= exp) h = find_next(h, n, exp);
			else break;
			if(h < 0) break;
			if(max[k] == s) break;
			cnt++; max[k] = s; k = h; h += inc;
		}
		max[j] = s;

        if(cnt > mlen){
            mlen = cnt; mstart = j; mstep = s;
			if(mlen >= n - (inc + 1)) return;
        }
    }
    if(mlen * (inc+1) < n) calc(n, inc+1);
}

int main()
{
    int n = 0, count = 0;
    int i = 0, j = 0;

#ifndef ONLINE_JUDGE
    freopen("input.in", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);
    i = 0;
    while(i < n && scanf("%d ", &m[++i]) == 1) v[i-1] = i;

    quicksort(v, n);

    /* get rid of elements with same value */
    do_reform(&n);

    if(n <= 1){ printf("1\n%d", v[0]); return 0;}

    /* calc */
    calc(n-1, 1);

    // printf("%I64d, %I64d\n", cntr, cntr2);
    printf("%d\n", mlen + 1);

    i = mstart; j = i+1;
    printf("%d ", v[i]);
    while(count < mlen){
        if(m[v[j]] == m[v[i]] + mstep){
            count++;
            i = j;
            printf("%d ", v[i]);
        }
        j++;
    }

	return 0;
}

