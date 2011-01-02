#include "stdio.h"
#include "string.h"

#define MAX_LEN 250*80 + 1

#define OP_L 1
#define OP_R 2
#define OP_X 3

#define EXP_L 1
#define EXP_R 2

short p[MAX_LEN] = {0};
char op[MAX_LEN] = {0};
short count = 0, last = 0;
char line[MAX_LEN] = "";

int main(int argc, char* argv[])
{
    int len = 0, pos = 0, i = 0;
    char isend = 0, exp = EXP_L, c = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(!isend){
        gets(line + pos);
        if(line[pos] == 0){
            line[pos++] = '\n';
            if(exp == EXP_R) op[last] = 0;
            exp = EXP_L;
            continue;
        }
        while(line[pos] != 0){
            if(line[pos] == '\\'){
                p[count] = pos;
                op[count] = OP_X;
                count++;
                if(memcmp(line + pos + 1, "endinput", 8) == 0){
                    if(exp == EXP_R) op[last] = 0;
                    isend = 1;
                    break;
                }
                if(memcmp(line + pos + 1, "par", 3) == 0){
                    if(exp == EXP_R) op[last] = 0;
                    exp = EXP_L;
                    pos += 4;
                }
                else if(line[pos+1] == '"') pos+=2;
                else pos++;
            }
            else if(line[pos] == '"'){
                if(exp == EXP_L){
                    last = count;
                    p[count] = pos;
                    op[count] = OP_L;
                    count++;
                    exp = EXP_R;
                } else if(exp == EXP_R){
                    p[count] = pos;
                    op[count] = OP_R;
                    count++;
                    exp = EXP_L;
                }
                pos++;
            }
            else if(line[pos] == '`' && line[pos+1] == '`'){
                if(exp == EXP_L) exp = EXP_R;
                pos += 2;
            }
            else if(line[pos] == '\'' && line[pos+1] == '\''){
                if(exp == EXP_R) exp = EXP_L;
                pos += 2;
            }
            else pos++;
        }
        if(!isend) line[pos++] = '\n';
    }

    len = pos;
    pos = 0;

    for(i = 0; i < count; i++){
        c = line[p[i]];
        line[p[i]] = 0;
        printf("%s", line+pos);
        if(op[i] == OP_L){
            printf("``");
        } else if(op[i] == OP_R){
            printf("''");
        } else if(op[i] == OP_X){
            printf("\\");
        }
        line[p[i]] = c;
        pos = p[i] + 1;
    }
    printf("%s", line+pos);

	return 0;
}
