#include "stdio.h"

int main(int argc, char* argv[])
{
    char t[7] = "", t2[7] = "", diff = 0, i = 0, d = 0;

    gets(t);

    diff = t[0] - t[3] + t[1] - t[4] + t[2] - t[5];
    if(diff != 1 && diff != -1){
        printf("No"); return 0;
    }

    for(d = 1, i = 5; i >= 0; i--){
        if(d != 0 && t[i] == 0x39) t2[i] = 0x30;
        else{
            t2[i] = t[i] + d; d = 0;
        }
    }
    diff = t2[0] - t2[3] + t2[1] - t2[4] + t2[2] - t2[5];

    if(diff == 0){
        printf("Yes"); return 0;
    }

    for(d = -1, i = 5; i >= 0; i--){
        if(d != 0 && t[i] == 0x30) t2[i] = 0x39;
        else{ t2[i] = t[i] + d; d = 0;}
    }
    diff = t2[0] - t2[3] + t2[1] - t2[4] + t2[2] - t2[5];

    if(diff != 0) printf("No");
    else printf("Yes");

	return 0;
}