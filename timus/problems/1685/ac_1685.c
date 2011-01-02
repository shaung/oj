#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    short right[101], rpos = 0;
    char line[20001] = "", rslt[20001] = "";
    int i = 0, j = 0, len = 0, l = 0, r = 0;

    memset(right, 0, sizeof(right));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(gets(line + len) != NULL){
        while(line[len] != 0) len++;
    }

    l = 0;
    right[rpos++] = len;

    for(i = 0; i < len; i++){
        r = right[rpos - 1];
        j = (l + r - 1) >> 1;
        /* printf("current pos: [%c]i=%d, l=%d, r = %d, j= %d\n", line[i], i, l, r, j); */
        rslt[j] = line[i];
        if(j == l){
            if((j + 1) == r) l = right[--rpos] + 1;
            else l = j + 1;
        }
        else right[rpos++] = j;
    }

    printf("%s\n", rslt);
    
    return 0;
}
