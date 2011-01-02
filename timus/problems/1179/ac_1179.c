#include "stdio.h"

int cnt[37] = {0}, status[37] = {0}, i = 0, j = 0;
char line[1048577] = "", *p = 0;

int main(int argc, char* argv[])
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
//    freopen("output.txt", "wt", stdout);
#endif

    while(gets(line) != NULL){
        for(p = line; ; p++){
            if(*p == 0x20 || *p == 0){
                for(j = 2; j <= 36; j++){
                    if(status[j] == 1){
                        cnt[j]++;
                        status[j] = 0;
                    }
                }
                if(*p == 0) break;
            }
            if(*p <= 0x31) i = 2;
            else if(*p <= 0x39) i = *p - 0x2F;
            else if(*p >= 0x41 && *p <= 0x5A) i = *p - 0x36;

            for(j = 2; j < i; j++){
                if(status[j] == 1){
                    cnt[j]++;
                    status[j] = 0;
                }
            }
            for(j = i; j <= 36; j++){
                if(status[j] == 0) status[j] = 1;
            }
        }
    }

    for(i = 0, j = 2; j <= 36; j++){
        if(status[j] == 1) cnt[j]++;
        if(cnt[j] > cnt[i]) i = j;
    }

    printf("%d %d", i, cnt[i]);
    

	return 0;
}
