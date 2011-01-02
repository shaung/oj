#include "stdio.h"
#include "string.h"

#define N_MAX 10001
#define VAL(X)   m[v[X]]
#define DIFF(X, Y)   m[v[X]] - m[v[Y]]

int m[N_MAX] = {0}, v[N_MAX] = {0}, offset[N_MAX] = {0};
int left[N_MAX] = {2}, right[N_MAX] = {2}, len[N_MAX] = {0}, head[3], max_len=0;
int l[N_MAX][N_MAX];

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

void foo(int n){
    int i = 0, j = 0, k = 0;
    int diff = 0;

    for(j = n; j >= 0; j--){
        i = j - 1;
        k = j + 1;
        while(i >= 0 && k <= n){
            diff = (VAL(i) + VAL(k)) - 2*VAL(j);
            if(diff < 0){
                k++;
            } else if(diff > 0){
                l[i][j] = 2;
                i--;
            } else {
                l[i][j] = l[j][k] + 1;
                if(l[i][j] > max_len){
                    max_len = l[i][j];
                    head[0] = i;
                    head[1] = j;
                }
                i--; k++;
            }
        }
        for(; i >= 1; i--){
            l[i][j] = 2;
        }
    }
    printf("maxlength=%d, starts with %d, %d\n", max_len, VAL(head[0]), VAL(head[1]));
}

void calc_offset(int n){
    int i = 0, j = 0;
    int x = 0;
    int maxcnt = 0, maxstep = 0, maxstart = 0;
    int cnt = 0, step = 0, start = 0;

    offset[v[0]] = 0;
    for(i = 1; i < n; i++){
        offset[v[i]] = m[v[i]] - m[v[i-1]];
    }

/*
    for(i = 0; i < n; i++){
        printf("%d %d\n", m[v[i]], offset[v[i]]);
    }
*/
 
    for(i = 1; i < n; i++){
        cnt = 2;
        start = i - 1;
        x = step = offset[v[i]];
        if(step == 0) continue;
        //printf("trying step=%d, start=%d\n", step, m[v[i]]);
        for(j = i + 1; j < n; j++){
            x -= offset[v[j]];
            //printf(" checking forward %d %d, remained %d\n", j, m[v[j]], x);
            if(x < 0) break;
            else if(x == 0){
                //printf(" found forward %d\n", m[v[j]]);
                x = step;
                cnt++;
            }
        }
        x = step;
        //printf(" preparing to checking backward, remained %d\n", x);
        for(j = i - 1; j > 0; j--){
            x -= offset[v[j]];
            //printf(" checking backward %d %d, remained %d\n", j, m[v[j]], x);
            if(x < 0) break;
            else if(x == 0){
                //printf(" found backward %d\n", m[v[j]]);
                x = step;
                cnt++;
                start = j - 1;
            }
        }
        if(cnt > maxcnt){
            maxcnt = cnt;
            maxstep = step;
            maxstart = start;
        }
    }

/*
    printf("maxcnt=%d, step=%d, start=%d, vstart=%d\n", maxcnt, maxstep, maxstart, m[v[maxstart]]);
    step = maxstep;
    for(i = maxstart; i < n - 1; i++){
        step -= offset[v[i+1]];
        //printf("checking %d, remain %d, ", m[v[i+1]], step);
        if(step == 0){
            step = maxstep;
            printf(" %d", m[v[i+1]]);
        }
        else if (step < 0) break;
    }
    printf("\n----\n");
*/

    printf("%d\n", maxcnt);
    printf("%d", v[maxstart]);
    step = maxstep;
    for(i = maxstart; i < n - 1; i++){
        step -= offset[v[i+1]];
        if(step == 0){
            step = maxstep;
            printf(" %d", v[i+1]);
        }
        else if (step < 0) break;
    }
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

typedef long long int64;
int64 cntr = 0, cntr2 = 0;
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

    scanf("%d\n", &n);
    i = 0;
    while(i < n && scanf("%d ", &m[++i]) == 1) v[i-1] = i;

    quicksort(v, n);

    /* get rid of elements with same value */
    do_reform(&n);

    if(n <= 1){
        printf("1\n%d", v[0]);
        return 0;
    }
    else if(n == 2){
        printf("2\n%d %d", v[0], v[1]);
        return 0;
    }
    else foo(n);

    /* calc */
    /*
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
    */

    return 0;
}

