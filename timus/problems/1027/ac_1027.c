#include "stdio.h"

#define C_OUTSIDE    0
#define C_IN_EXP     1
#define C_IN_CMT     2

#define IS_EXP(x)  ((x == '=') || (x == '+') || (x == '-') || (x == '*') || (x == '/') || \
                    ((x >= 0x30) && (x <= 0x39)))

int main(int argc, char* argv[])
{
    char line[10000] = "", status = C_OUTSIDE, prev_status = 0, *p = 0, prev = 0, rslt = 0;
    short depth = 0;

    int i = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
#endif

    while(gets(line) != NULL){
        for(p = line; *p != 0; p++){
            if(status == C_OUTSIDE){
                if(prev == '('){
                    if(*p == '*'){
                        prev_status = status;
                        prev = 0;
                        status = C_IN_CMT;
                        continue;
                    }
                    else if(*p == '('){
                       status = C_IN_EXP;
                       depth = 2;
                    }
                    else if(IS_EXP(*p)){
                       status = C_IN_EXP;
                       depth = 1;
                    } else if(*p != ')'){
                        rslt = 1;
                        break;
                    }
                } else if(*p == ')'){
                    rslt = 1;
                    break;
                }
            }
            else if(status == C_IN_EXP){
                if(prev == '(' && *p == '*'){
                    depth--;
                    prev_status = status;
                    prev = 0;
                    status = C_IN_CMT;
                    continue;
                }
                else if(*p == '('){
                   depth++;
                } else if(*p == ')'){
                    if(--depth == 0){
                        status = C_OUTSIDE;
                    }
                } else if(!IS_EXP(*p)){
                    rslt = 1;
                    break;
                }
            }
            else if(status == C_IN_CMT){
                if(*p == ')' && prev == '*'){
                    status = prev_status;
                }
            }
            prev = *p;
        }

        if(rslt == 1){
            printf("NO");
            return 0;
        }
    }

    if(status != C_OUTSIDE || prev == '('){
        printf("NO");
        return 0;
    }

    printf("YES");
    
    return 0;
}
