#include "stdio.h"

int main(int argc, char* argv[])
{
    int t1, t2, sum = 0, i, j;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d %d\n", &t1, &t2);

    for(i = 0; i < 10; i++){
        scanf("%d ", &j);
        sum += j*20;
    }

    if(t1 + sum > t2) printf("Dirty debug :(");
    else printf("No chance.");

	return 0;
}
