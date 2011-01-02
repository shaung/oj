#include "stdio.h"
#include "string.h"
#include "math.h"

int main(int argc, char* argv[])
{
    char rslt[1000000];
    double num = -1;
    int i = 0;
    int buf = 0;

    memset(rslt, 0, sizeof(rslt));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif
    
    while(1){
        buf = getchar();
        if(buf >= 0x30 && buf <= 0x39){
            if(num == -1) num = 0;
            num = num * 10.0 + (buf - 0x30);
        }
        else{
            if(num >= 0){
                i += sprintf(rslt + i, "%.4f", sqrt(num));
                i++;
                num = -1;
            }
            if(buf == EOF)break;
        }
    }

    while(i > 0){
        i--;
        if(rslt[i-1] == 0 || i == 0)
           printf("%s\n", rslt + i);
    }

	return 0;
}
