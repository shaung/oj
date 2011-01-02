#include "stdio.h"

int main(int argc, char* argv[])
{
    char line[20] = "";
    short cnt[3] = {0};
    short n = 0, i = 0, max = 0, rslt = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        gets(line);
        if(line[0] == 'E') cnt[0]++;
        else if(line[0] == 'L') cnt[1]++;
        else if(line[0] == 'M') cnt[2]++;
    }

    for(i = 1, rslt = 0, max = cnt[0]; i < 3; i++){
        if(cnt[i] > max){
            rslt = i;
            max = cnt[i];
        }
    }

    if(rslt == 0) printf("Emperor Penguin");
    else if(rslt == 1) printf("Little Penguin");
    else if(rslt == 2) printf("Macaroni Penguin");

	return 0;
}
