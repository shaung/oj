#include "stdio.h"
#include "string.h"

#define OP_END 0x00000001 /*  0 */
#define OP_GOT 0x00000002 /*  1 */
#define OP_PRT 0x00000004 /*  2 */
#define OP_IS  0x00000008 /*  3 */
#define OP_NOT 0x00000010 /*  4 */
#define OP_ADD 0x00000020 /*  5 */
#define OP_SUB 0x00000040 /*  6 */
#define OP_MUL 0x00000080 /*  7 */
#define OP_DIV 0x00000100 /*  8 */
#define OP_MOD 0x00000200 /*  9 */
#define OP_OR  0x00000400 /* 10 */
#define OP_AND 0x00000800 /* 11 */
#define OP_XOR 0x00001000 /* 12 */
#define OP_EQU 0x00002000 /* 13 */
#define OP_NEQ 0x00004000 /* 14 */
#define OP_BOE 0x00008000 /* 15 */
#define OP_BIG 0x00010000 /* 16 */
#define OP_SML 0x00020000 /* 17 */
#define OP_SOE 0x00040000 /* 18 */
#define OP_LFT 0x01000000 /* 24 */
#define OP_RHT 0x02000000 /* 25 */

char vname[2000][51];
int v[2000];
char vinit[2000];
short vcnt = 0;

int step = 0;
int cmdcnt = 0;

/* 0 : 0 [end]  1 [goto] 2 [print]        */
/*     3 [=]    4 [not]                   */
/*     5 [+]    6 [-]    7 [*]   8 [/]    */
/*     9 [%]    10 [or]  11[and] 12 [xor] */
/*     13 [if==]  14 [if!=]  15 [if>=]    */
/*     16 [if>]   17 [if<=]  18 [if<]     */
/*     24 [left variable flag]  25 [right flag]  */
/* 1 : destination variable no  or label no  */
/* 2 : left src variable no or number  */
/* 3 : right src variable no or number  */
int cmd[2001][4];
char lbname[2000][51];
short label[2000];
short lcnt = 0;

int getvno(char *name);
int getlno(char *name);

void printv();
void sortv();

int isnum(char a);
int tonum(char *);
void lower(char *);
int mod(int a, int b);

int precompile(char *line);
int exec(int lineno);

int main(int argc, char* argv[])
{
    int i = 0, cur = 0;
    char line[10000] = "";

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
/*
    printf(" 0%%6 = %d\n", mod(0, -6));
    printf("-1%%6 = %d\n", mod(-1, 6));
    printf("-2%%6 = %d\n", mod(-2, 6));
    printf("-3%%6 = %d\n", mod(-3, 6));
    printf("-4%%6 = %d\n", mod(-4, 6));
    printf("-5%%6 = %d\n", mod(-5, 6));
    printf("-6%%6 = %d\n", mod(-6, 6));
    printf("-7%%6 = %d\n", mod(-7, 6));
    printf("-8%%6 = %d\n", mod(-8, 6));
    printf("1%%6 = %d\n", mod(1, 6));
    printf("2%%6 = %d\n", mod(2, 6));
    printf("3%%6 = %d\n", mod(3, 6));
    printf("4%%6 = %d\n", mod(4, 6));
    printf("5%%6 = %d\n", mod(5, 6));
    printf("6%%6 = %d\n", mod(6, 6));
    printf("7%%6 = %d\n", mod(7, 6));
    printf("8%%6 = %d\n", mod(8, 6));
    printf("2499999%%-6 = %d\n", mod(2499999, -6));
    printf("-2499999%%-6 = %d\n", mod(-2499999, -6));
    printf(" 0%%-6 = %d\n", mod(0, -6));
    printf("-1%%-6 = %d\n", mod(-1, -6));
    printf("-2%%-6 = %d\n", mod(-2, -6));
    printf("-3%%-6 = %d\n", mod(-3, -6));
    printf("-4%%-6 = %d\n", mod(-4, -6));
    printf("-5%%-6 = %d\n", mod(-5, -6));
    printf("-6%%-6 = %d\n", mod(-6, -6));
    printf("-7%%-6 = %d\n", mod(-7, -6));
    printf("-8%%-6 = %d\n", mod(-8, -6));
    printf("1%%-6 = %d\n", mod(1, -6));
    printf("2%%-6 = %d\n", mod(2, -6));
    printf("3%%-6 = %d\n", mod(3, -6));
    printf("4%%-6 = %d\n", mod(4, -6));
    printf("5%%-6 = %d\n", mod(5, -6));
    printf("6%%-6 = %d\n", mod(6, -6));
    printf("7%%-6 = %d\n", mod(7, -6));
    printf("8%%-6 = %d\n", mod(8, -6));
*/
#endif

    memset(v, 0, sizeof(v));
    memset(vinit, 0, sizeof(vinit));
    memset(vname, 0, sizeof(vname));
    memset(label, 0, sizeof(label));
    memset(lbname, 0, sizeof(lbname));
    memset(cmd, 0, sizeof(cmd));

    while(gets(line) != NULL){
        step += precompile(line);
    }

    while(1){
        cur = exec(cur);
        if(cur < 0) break;
        if(cmdcnt >= 10000000){
            printf("Program terminated. Variables state:\n");
            printv();
            return 0;
        }
    }

	return 0;
}

int getvno(char *name){
    int i = 0;
    for(i = 0; i < vcnt; i++){
        if(strcmp(name, vname[i]) == 0){
            return i;
        }
    }
    /* not found */
    memcpy(vname[vcnt++], name, strlen(name));
    return vcnt-1;
}

int getlno(char *name){
    int i = 0;
    for(i = 0; i < lcnt; i++){
        if(strcmp(name, lbname[i]) == 0){
            return i;
        }
    }
    /* not found */
    memcpy(lbname[lcnt], name, strlen(name));
    return lcnt++;
}

void printv(){
    int i = 0;

    sortv();
    
    for(i = 0; i < vcnt; i++){
        if(vinit[i] == 1)
            printf("%s: %d\n", vname[i], v[i]);
    }
}

void sortv(){
    int i = 0, j = 0, k = 0, pos = 0, cmp = 0, tmpvalue = 0;
    char tmp[51];

    for(i = vcnt - 1; i >= 0; i--){
        for(j = 0; j < i; j++){
            if(strcmp(vname[j] ,vname[j+1]) > 0){
                memcpy(tmp, vname[j], sizeof(tmp));
                memcpy(vname[j], vname[j+1], sizeof(tmp));
                memcpy(vname[j+1], tmp, sizeof(tmp));
                tmpvalue = v[j];
                v[j] = v[j+1];
                v[j+1] = tmpvalue;
                tmpvalue = vinit[j];
                vinit[j] = vinit[j+1];
                vinit[j+1] = tmpvalue;
            }
        }
    }
}

int precompile(char *line){
    int i = 0, j = 0, k = 0, status = 0;
    char item[10][100];
    int icnt = 0;

    for(i = 0; line[i] != 0; i++){
        if(line[i] == 0x20){
            if(status == 1){
                item[icnt][j] = 0;
                if(item[icnt][j-1] == ':'){
					item[icnt][j-1] = 0;
					lower(item[icnt]);
					label[getlno(item[icnt])] = step;
					memset(item[icnt], 0, sizeof(item[icnt]));
                } else icnt++;
                status = 0;
            }
        } else {
            if(status == 0){
                j = 0;
                item[icnt][j++] = line[i];
                status = 1;
            } else {
                item[icnt][j++] = line[i];
            }
            if(line[i + 1] == 0){
                item[icnt][j] = 0;
                if(item[icnt][j-1] == ':'){
					item[icnt][j-1] = 0;
					lower(item[icnt]);
					label[getlno(item[icnt])] = step;
					memset(item[icnt], 0, sizeof(item[icnt]));
                } else icnt++;
            }
        }
    }

    switch(icnt){
    case 0:
        return 0;
    case 1:
        /* end */
        cmd[step][0] = OP_END;
        break;
    case 2:
        lower(item[0]);
        /* print */
        if(strcmp(item[0], "print") == 0){
            cmd[step][0] = OP_PRT;
            if(isnum(item[1][0]) == 0){
                cmd[step][0] |= OP_LFT;
                cmd[step][1] = getvno(item[1]);
            } else {
                cmd[step][1] = tonum(item[1]);
            }
        }
        /* goto without condition */
        else if(strcmp(item[0], "goto") == 0){
            cmd[step][0] = OP_GOT;
			lower(item[1]);
            cmd[step][1] = getlno(item[1]);
        }
        break;
    case 3:
        /* v1 = v2 */
        cmd[step][0] = OP_IS;
        cmd[step][1] = getvno(item[0]);
        if(isnum(item[2][0]) == 0){
            cmd[step][0] |= OP_LFT;
            cmd[step][2] = getvno(item[2]);
        } else {
            cmd[step][2] = tonum(item[2]);
        }
        break;
    case 4:
        /* v1 = not v2 */
        cmd[step][0] = OP_NOT;
        cmd[step][1] = getvno(item[0]);
        if(isnum(item[3][0]) == 0){
            cmd[step][0] |= OP_LFT;
            cmd[step][2] = getvno(item[3]);
        } else {
            cmd[step][2] = tonum(item[3]);
        }
        break;
    case 5:
        /* v1 = v2 ? v3 */
        if(item[3][0] == '+') cmd[step][0] = OP_ADD;
        else if(item[3][0] == '-') cmd[step][0] = OP_SUB;
        else if(item[3][0] == '*') cmd[step][0] = OP_MUL;
        else if(item[3][0] == '/') cmd[step][0] = OP_DIV;
        else if(item[3][0] == '%') cmd[step][0] = OP_MOD;
        else if(item[3][0] == 'o' || item[3][0] == 'O') cmd[step][0] = OP_OR;
        else if(item[3][0] == 'a' || item[3][0] == 'A') cmd[step][0] = OP_AND;
        else if(item[3][0] == 'x' || item[3][0] == 'X') cmd[step][0] = OP_XOR;

        cmd[step][1] = getvno(item[0]);

        if(isnum(item[2][0]) == 0){
            cmd[step][0] |= OP_LFT;
            cmd[step][2] = getvno(item[2]);
        } else {
            cmd[step][2] = tonum(item[2]);
        }

        if(isnum(item[4][0]) == 0){
            cmd[step][0] |= OP_RHT;
            cmd[step][3] = getvno(item[4]);
        } else {
            cmd[step][3] = tonum(item[4]);
        }

        break;
    case 6:
        /* if <varnum> == <varnum> goto <label>  */
        if(item[2][0] == '=' && item[2][1] == '=')
            cmd[step][0] = OP_EQU;
        else if(item[2][0] == '!' && item[2][1] == '=')
            cmd[step][0] = OP_NEQ;
        else if(item[2][0] == '>' && item[2][1] == '=')
            cmd[step][0] = OP_BOE;
        else if(item[2][0] == '>' && item[2][1] == 0)
            cmd[step][0] = OP_BIG;
        else if(item[2][0] == '<' && item[2][1] == '=')
            cmd[step][0] = OP_SOE;
        else if(item[2][0] == '<' && item[2][1] == 0)
            cmd[step][0] = OP_SML;

        lower(item[5]);
        cmd[step][1] = getlno(item[5]);

        if(isnum(item[1][0]) == 0){
            cmd[step][0] |= OP_LFT;
            cmd[step][2] = getvno(item[1]);
        } else {
            cmd[step][2] = tonum(item[1]);
        }

        if(isnum(item[3][0]) == 0){
            cmd[step][0] |= OP_RHT;
            cmd[step][3] = getvno(item[3]);
        } else {
            cmd[step][3] = tonum(item[3]);
        }

        break;
    }

    return 1;
}

int exec(int lineno){
    int x = 0, y = 0;
    int *cmdnow = cmd[lineno];

    cmdcnt++;

    switch(cmdnow[0] & 0xFFFFFF){
    case OP_END:
    case OP_PRT:
    case OP_GOT:
    case OP_IS:
    case OP_NOT:
        break;
    case OP_ADD:
    case OP_SUB:
    case OP_MUL:
    case OP_DIV:
    case OP_MOD:
    case OP_OR:
    case OP_AND:
    case OP_XOR:
        vinit[cmdnow[1]] = 1;
    case OP_EQU:
    case OP_NEQ:
    case OP_BOE:
    case OP_BIG:
    case OP_SOE:
    case OP_SML:
        if((cmdnow[0] & OP_LFT) == OP_LFT){
            x = v[cmdnow[2]];
            vinit[cmdnow[2]] = 1;
        } else x = cmdnow[2];
        if((cmdnow[0] & OP_RHT) == OP_RHT){
            y = v[cmdnow[3]];
            vinit[cmdnow[3]] = 1;
        } else y = cmdnow[3];
        break;
    default:
        return -1;
    }

    switch(cmdnow[0] & 0xFFFFFF){
    case OP_END:
        return -2;
    case OP_PRT:
        if((cmdnow[0] & OP_LFT) == OP_LFT){
            vinit[cmdnow[2]] = 1;
            printf("%d\n", v[cmdnow[1]]);
        } else {
            printf("%d\n", cmdnow[1]);
        }
        break;
    case OP_GOT:
        return label[cmdnow[1]];
        break;
    case OP_IS:
        if((cmdnow[0] & OP_LFT) == OP_LFT){
            v[cmdnow[1]] = v[cmdnow[2]];
            vinit[cmdnow[2]] = 1;
        } else {
            v[cmdnow[1]] = cmdnow[2];
        }
        vinit[cmdnow[1]] = 1;
        break;
    case OP_NOT:
        if((cmdnow[0] & OP_LFT) == OP_LFT){
            v[cmdnow[1]] = ~v[cmdnow[2]];
            vinit[cmdnow[2]] = 1;
        } else {
            v[cmdnow[1]] = ~cmdnow[2];
        }
        vinit[cmdnow[1]] = 1;
        break;
    case OP_ADD:
        v[cmdnow[1]] = x + y;
        break;
    case OP_SUB:
        v[cmdnow[1]] = x - y;
        break;
    case OP_MUL:
        v[cmdnow[1]] = x * y;
        break;
    case OP_DIV:
        v[cmdnow[1]] = x / y;
        break;
    case OP_MOD:
        v[cmdnow[1]] = mod(x, y);
        break;
    case OP_OR:
        v[cmdnow[1]] = x | y;
        break;
    case OP_AND:
        v[cmdnow[1]] = x & y;
        break;
    case OP_XOR:
        v[cmdnow[1]] = x ^ y;
        break;
    case OP_EQU:
        if(x == y) return label[cmdnow[1]];
        break;
    case OP_NEQ:
        if(x != y) return label[cmdnow[1]];
        break;
    case OP_BOE:
        if(x >= y) return label[cmdnow[1]];
        break;
    case OP_BIG:
        if(x > y) return label[cmdnow[1]];
        break;
    case OP_SOE:
        if(x <= y) return label[cmdnow[1]];
        break;
    case OP_SML:
        if(x < y) return label[cmdnow[1]];
        break;
    default:
        return -1;
    }

    return lineno + 1;
}

int isnum(char a){
    return ((a == 0x2D || ((a >= 0x30) && (a <= 0x39))) ? 1 : 0);
}

int tonum(char *line){
    int i = 0, rslt = 0;
    for(rslt = 0, i = 0; line[i] != 0; i++){
        if(line[i] >= 0x30 && line[i] <= 0x39)
            rslt = rslt * 10 + line[i] - 0x30;
    }
    if(line[0] == '-')
        rslt *= -1;
    return rslt;
}

/* minimal non-negative r such that (a - r) % b == 0  */
int mod(int a, int b){
    if(b < 0) b = 0 - b;
    if(a < 0) a = (a - (a/b)*b) + b;
    return a%b;
}

void lower(char *line){
    int i = 0;
    for(i = 0; line[i] != 0; i++){
        if((line[i] >= 0x41) && (line[i] <= 0x5A))
            line[i] += 0x20;
    }
}

