#include "stdio.h"
#include "string.h"

char dicname[5100][51];
int dicsize = 0;
int h[100][51];
char pno[101] = "";
int lenpno = 0;

int rslt[100] = {0}, mincnt[100] = {0};

int to_num(char *in, char *out);
void calcword(char *word);
void judge();

int main(int argc, char* argv[])
{
    int n = 0, i = 0, j = 0;
    char line[51] = "";

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    while(1){
        if(gets(pno) == NULL) break;
        if(pno[0] == '-' || pno[0] == 0) break;
        lenpno = strlen(pno);

        memset(dicname, 0, sizeof(dicname));
        dicsize = 0;

        memset(h, -1, sizeof(h));
        memset(rslt, 0 ,sizeof(rslt));
        memset(mincnt, 0 ,sizeof(mincnt));

        scanf("%d\n", &n);

        for(i = 0; i < n; i++){
            gets(line);
            calcword(line);
        }

        judge();

        if(rslt[0] == 0){
            printf("No solution.\n");
        } else {
			for(i = 0; i < lenpno; i += rslt[i]){
				if(i > 0) printf(" ");
				printf("%s", dicname[h[i][rslt[i]]]);
			}
			printf("\n");
        }
    }
    
    return 0;
}

/* dp */
void judge(){
	int i = 0, j = 0;
	for(i = lenpno - 1; i >= 0; i--){
        if(lenpno - i <= 50){
    		if(h[i][lenpno - i] >= 0){
	    		rslt[i] = lenpno - i;
		    	mincnt[i] = 1;
/*
#ifndef ONLINE_JUDGE
			printf("[%d] found just size:%s\n", i, dicname[h[i][rslt[i]]]);
#endif
*/
			    continue;
    		}
        }
		for(mincnt[i] = lenpno + 1, j = i + 1; (j < lenpno) && (j-i) <= 50; j++){
			if(rslt[j] == 0) continue;
			if(h[i][j-i] < 0) continue;
			if(mincnt[i] > 1 + mincnt[j]){
				mincnt[i] = 1 + mincnt[j];
				rslt[i] = j - i;
/*
#ifndef ONLINE_JUDGE
				printf("[%d] by far best:%s\n", i, dicname[h[i][rslt[i]]]);
#endif
*/
			}
		}
	}
}

void calcword(char *word){
    char num[51] = "";
    int lenw = 0, found = 0, possible = 0;
    int i = 0, j = 0;

    lenw = to_num(word, num);

    for(i = 0; i <= lenpno - lenw; i++){
		if(h[i][lenw] >= 0) continue;
        for(found = 1, j = 0; j < lenw; j++){
            if(pno[j + i] != num[j]){
                found = 0;
                break;
            }
        }
        if(found == 1){
            h[i][lenw] = dicsize;
            possible = 1;
        }
    }

    if(possible == 1){
        memcpy(dicname + dicsize, word, lenw + 1);
		dicsize++;
    }
}

int to_num(char *in, char *out){
    int i = 0;
    for(i = 0; ; i++){
        switch(in[i]){
        case 'o':
        case 'q':
        case 'z':
            out[i] = '0';
            break;
        case 'i':
        case 'j':
            out[i] = '1';
            break;
        case 'a':
        case 'b':
        case 'c':
            out[i] = '2';
            break;
        case 'd':
        case 'e':
        case 'f':
            out[i] = '3';
            break;
        case 'g':
        case 'h':
            out[i] = '4';
            break;
        case 'k':
        case 'l':
            out[i] = '5';
            break;
        case 'm':
        case 'n':
            out[i] = '6';
            break;
        case 'p':
        case 'r':
        case 's':
            out[i] = '7';
            break;
        case 't':
        case 'u':
        case 'v':
            out[i] = '8';
            break;
        case 'w':
        case 'x':
        case 'y':
            out[i] = '9';
            break;
        default:
            out[i] = in[i];
        }
        if(in[i] == 0) break;
    }

    return i;
}
