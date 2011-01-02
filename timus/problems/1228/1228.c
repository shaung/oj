#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int n = 0;
    unsigned int s = 0;
    short i = 0, j = 0;
    char line[50];
    unsigned int d[21];

    memset(d, 0, sizeof(d));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %u\n", &n, &s);

    if(n == 1){
        printf("%d", s - 1);
        return 0;
    }

    d[0] = s;
    for(i = 1; i <= n; i++){
        gets(line);
        for(d[i] = 0, j = 0; line[j] != 0x20 && line[j] != 0; j++)
            d[i] = d[i] * 10 + (line[j] - 0x30);
        printf("%d", (d[i-1] / d[i]) - 1);
        if(i != n) printf(" ");
    }

	return 0;
}
