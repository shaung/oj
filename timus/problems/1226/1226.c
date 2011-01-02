#include "stdio.h"

int main(int argc, char* argv[])
{
    char line[256] = "";
    short i = 0, s = 0, e = 0, first = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(gets(line) != NULL){
        if(first == 0) first = 1;
        else printf("\n");

        s = -1; e = -1;
        for(i = 0 ;; i++){
            if((line[i] >= 0x41 && line[i] <= 0x5A) ||
               (line[i] >= 0x61 && line[i] <= 0x7A)){
                if(s == -1)s = i;
                e = i;
            } else {
                if(s >= 0){
                    while(e >= s) printf("%c", line[e--]);
                    s = -1;
                }
                if(line[i] == 0) break;
                printf("%c", line[i]);
            }
        }
    }

    return 0;
}
