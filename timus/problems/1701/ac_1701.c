#include "stdio.h"
#include "string.h"

struct vector{int next, amount;};

struct vector v[50001];

int find_root(int index);
void my_swap(int *x, int*y);

int main(int argc, char* argv[])
{
    int n = 0, m = 0, i = 0;
	int x, y, rx, ry;
	int diff, amountx, amounty;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    memset(v, 0, sizeof(v));

	for(i = 0; i < 50001; i++){
		v[i].next = -1;
	}

    scanf("%d %d\n", &n, &m);

    for(i = 0; i < m; i++){
        scanf("%d %d %d\n", &x, &y, &diff);

        if(diff < 0){
            diff *= -1;
            my_swap(&x, &y);
        }

		/* make sure that y = x - diff */

        if(x < 0 || x >= n || y < 0 || y >= n) break;
        if(x == 0){
			if(diff > 0) break;
			else my_swap(&x, &y);
		}

		if(x == y){
			if(diff == 0) continue;
			else break;
		}

		/* match */
		rx = find_root(x);
		ry = find_root(y);

		amountx = v[x].amount;
		amounty = v[y].amount;

		/* if in the same set */
		if(rx == ry){
			if(amountx - amounty != diff) break;
		}
		/* if amount(y) < amount(x), attach set(x) to set(y) */
		else if(amounty - amountx + diff >= 0){
			if(rx == 0){
				if(diff > 0) break;
				else my_swap(&rx, &ry);
			}
			v[rx].next = ry;
			v[rx].amount = amounty - amountx + diff;
		}
		/* otherwise attach set(y) to set(x) */
		else {
			if(ry == 0){
				if(diff > 0) break;
				else my_swap(&rx, &ry);
			}
			v[ry].next = rx;
			v[ry].amount = amountx - amounty - diff;
		}
    }
    
    if(i < m){
        printf("Impossible after %d statements", i + 1);
    } else {
        printf("Possible\n");
		for(i = 0; i < n; i++){
			find_root(i);
			printf("%d\n", v[i].amount);
		}
    }

    return 0;
}

int find_root(int index){
	int prev_next = 0;
	if(v[index].next == -1){
        return index;
    } else {
		prev_next = v[index].next;
        v[index].next = find_root(v[index].next);
		if(prev_next != -1)
	        v[index].amount += v[prev_next].amount;
    }

	return v[index].next;
}

void my_swap(int *x, int*y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}