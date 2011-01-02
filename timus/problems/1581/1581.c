#include "stdio.h"

struct element{short cnt, num;};

int main(int argc, char* argv[])
{
    short n = 0, i = 0, now = 0, prev = 0, vcnt = 0;
    struct element v[1000];

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        scanf("%d ", &now);
        if(now == prev) v[vcnt-1].cnt++;
        else {
            v[vcnt].num = now;
            v[vcnt].cnt = 1;
            vcnt++;
            prev = now;
        }
    }

    for(i = 0; i < vcnt; i++){
        printf("%d %d ", v[i].cnt, v[i].num);
    }

	return 0;
}
