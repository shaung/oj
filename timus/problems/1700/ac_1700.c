#include "stdio.h"
#include "string.h"

#define MAX_PRIME 3731937197
#define IS_CHAR(x)  (((x) >= 0x41 && (x) <= 0x5A) || ((x) >= 0x61 && (x) <= 0x7A))

struct t_word{unsigned int code; unsigned short line, pos, len;};
struct t_set{unsigned int code; short szname, szkw, kw[125];};

struct t_word dic[125000];
int szdic = 0;
struct t_set set[1000];
int n = 0;
int curkw[125], szcurkw = 0, minkw = 0, cset = 0;

unsigned int hash(char *str);
int lookup_word(char *str, unsigned short line, unsigned short pos, unsigned short len);
int lookup_set(char *str);

char line[1000][251];
char curline[251] = "";
int curset[125], szcurset = 0;

int main(int argc, char* argv[])
{
    int m = 0, i = 0, j = 0, k = 0, h = 0, l = 0, start = 0, found = 0, tmp = 0;
    
    memset(line, 0, sizeof(line));
    memset(set, 0, sizeof(set));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);
    for(i = 0; i < n; i++){
        gets(line[i]);
        for(j = 0; line[i][j] != ':'; j++);
        set[i].szname = j++;
        set[i].code = hash(line[i]);
        while(line[i][j] == 0x20) j++;

        for(start = j; ; j++){
            if(line[i][j] >= 0x61 && line[i][j] <= 0x7A){
                if(start == -1) start = j;
            }
            else{
                set[i].kw[set[i].szkw++] = lookup_word(line[i] + start, i, start, j - start);

                while(line[i][j+1] == 0x20) j++;
                if(line[i][j] == 0) break;
                line[i][j] = 0;
                start = -1;
            }
        }
    }

    scanf("%d\n", &m);

    for(i = 0; i < m; i++){
        gets(curline);

        memset(curset, 0, sizeof(curset));
        memset(curkw, 0, sizeof(curkw));
        szcurset = 0;
        szcurkw = 0;

        minkw = 125000;
        cset = 0;
        for(start = 0, j = 0; ; j++){
            if(curline[j] == 0x20 || curline[j] == 0){
                curset[szcurset] = lookup_set(curline + start);
                if(set[curset[szcurset]].szkw < minkw){
                    minkw = set[curset[szcurset]].szkw;
                    cset = curset[szcurset];
                }
                szcurset++;
                if(curline[j] == 0) break;
                while(curline[j+1] == 0x20)j++;
                start = j+1;
            }
        }

        for(j = 0; j < set[cset].szkw; j++){
            h = set[cset].kw[j];
            for(k = 0; k < szcurset; k++){
                if(curset[k] == cset) continue;
                for(found = 0, l = 0; l < set[curset[k]].szkw; l++){
                    if(h == set[curset[k]].kw[l]){
                       found = 1;
                       break;
                    }
                }
                if(found == 0) break;
            }
            if(found != 0) curkw[szcurkw++] = h;
        }

        if(szcurkw == 0) printf("No solution.\n");
        else{
            for(j = szcurkw-1; j > 0; j--){
                for(k = 0; k < j; k++){
                    if(strcmp(line[dic[curkw[k]].line] + dic[curkw[k]].pos,
                        line[dic[curkw[k+1]].line] + dic[curkw[k+1]].pos) > 0){
                        tmp = curkw[k];
                        curkw[k] = curkw[k+1];
                        curkw[k+1] = tmp;
                    }
                }
            }
            for(j = 0; j < szcurkw; j++){
                if(j > 0) printf(" ");
                printf("%s", line[dic[curkw[j]].line] + dic[curkw[j]].pos);
            }
            printf("\n");
        }
    }

	return 0;
}

unsigned int hash(char *str){
    unsigned int rslt = 1;
    unsigned char *p = 0;
    for(p = (unsigned char*)str; IS_CHAR(*p); p++){
        rslt = rslt * 31 + *p - 0x41;
    }
    return rslt % MAX_PRIME;
}

int lookup_word(char *str, unsigned short lno, unsigned short pos, unsigned short len){
    unsigned int code = hash(str);
    int i = 0;
    for(i = 0; i < szdic; i++){
        if(dic[i].code == code){
            if(memcmp(line[dic[i].line] + dic[i].pos, str, (dic[i].len) * sizeof(char)) == 0 &&
                (*(str + dic[i].len) == 0x20 || *(str + dic[i].len) == 0)){
                return i;
            }
        }
    }

    dic[szdic].code = code;
    dic[szdic].line = lno;
    dic[szdic].pos = pos;
    dic[szdic].len = len;

    szdic++;

    return (szdic - 1);
}

int lookup_set(char *str){
    unsigned int code = hash(str);
    int i = 0;
    for(i = 0; i < n; i++){
        if(set[i].code == code){
            if(memcmp(line[i], str, set[i].szname) == 0) return i;
        }
    }

    return -1;
}
