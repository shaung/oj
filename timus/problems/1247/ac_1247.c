#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int s = 0, n = 0;
    int i = 0, j = 0;
    int a = 0, sum = 0;
    char line[4] = "";

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d\n", &s, &n);

    /* sum(1..s) == S + N  && sum(i..j) <= N + j - i + 1 */
    /* equals  sum(i..j) <= N */

    for(i = 0; i < s; i++){
        gets(line);
        
	    for(a = 0, j = 0; line[j] != 0x20 && line[j] != 0; j++)
		    a = a * 10 + (line[j] - 0x30);

        sum += --a;
        if(a > n || sum > n || sum < 0){
            printf("NO");
            return 0;
        }
    }

    printf("YES");

	return 0;
}
