#include "stdio.h"

#define IS_CHAR(x)  (((x >= 0x41) && (x <= 0x5A)) || ((x >= 0x61) && (x <= 0x7A)))
#define IS_UPPER(x)  ((x >= 0x41) && (x <= 0x5A))
#define IS_LOWER(x)  ((x >= 0x61) && (x <= 0x7A))
#define IS_END(x)   ((x == '.') || (x == '?') || (x == '!'))

#define C_BEGIN  0
#define C_INW    1
#define C_OUTW   2

int main(int argc, char* argv[])
{
    char line[10000] = "";
    int i = 0, j = 0, status = 0, rslt = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    status = C_BEGIN;
    while(gets(line) != NULL){
        for(i = 0; ; i++){
            if(IS_CHAR(line[i])){
                switch(status){
                case C_BEGIN:
                    if(IS_LOWER(line[i])) rslt++;
                    status  = C_INW;
                    break;
                case C_INW:
                    if(IS_UPPER(line[i])) rslt++;
                    break;
                case C_OUTW:
                    status = C_INW;
                    break;
                }
            }
            else if(IS_END(line[i])){
                switch(status){
                case C_BEGIN:
                    break;
                case C_INW:
                case C_OUTW:
                    status = C_BEGIN;
                    break;
                }
            }
            else if(line[i] == 0){
                if(status == C_INW) status = C_OUTW;
                break;
            }
            else {
                if(status != C_BEGIN)
                    status = C_OUTW;
            }
        }
    }

    printf("%d", rslt);

	return 0;
}
