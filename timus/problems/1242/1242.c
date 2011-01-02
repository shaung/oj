#include "stdio.h"
#include "string.h"

struct villager{short prt[2], prtcnt, chdcnt, color; /* 0:unknown 1:dead 2:ascend 3:decend */};
struct villager v[1000];
int n = 0;

void setcolorprt(int no);
void setcolorchd(int no);

int main(int argc, char* argv[])
{

	char line[20] = "";
	int i = 0, j = 0, chd = 0, prt = 0;
    int bloodmode = 0;
	int found = 0;

    memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    while(gets(line) != NULL){
		if(line[0] == 'B'){
			bloodmode = 1;
			continue;
		}
		if(bloodmode == 1){
			for(chd = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
				chd = chd * 10 + (line[i] - 0x30);
			chd--;
			/* calc colors of parents */
			v[chd].color = 1;
			setcolorprt(chd);

			/* calc colors of children */
			setcolorchd(chd);

			continue;
		} else {
			for(chd = 0, i = 0; line[i] != 0x20 && line[i] != 0; i++)
				chd = chd * 10 + (line[i] - 0x30);
			chd--;
			for(prt = 0, i++; line[i] != 0x20 && line[i] != 0; i++)
				prt = prt * 10 + (line[i] - 0x30);
			prt--;
		}

		v[chd].prt[v[chd].prtcnt++] = prt;
		v[prt].chdcnt++;
    }

    /* calculate the maximum path as cycle not found */
    for(found = 0, j = 0; j < n; j++){
        if(v[j].color == 0){
			found = 1;
			printf(" %d", j + 1);
		}
    }

	if(found == 0)
	    printf("0");

	return 0;
}

void setcolorprt(int no){
	int i = 0;
	if(v[no].color == 0) v[no].color = 2;
	for(i = 0; i < v[no].prtcnt; i++){
		setcolorprt(v[no].prt[i]);
	}
}

void setcolorchd(int no){
	int i = 0, j = 0;
	if(v[no].chdcnt == 0) return;
	for(i = 0; i < n; i++){
		for(j = 0; j < v[i].prtcnt; j++){
			if(v[i].prt[j] == no){
				v[i].color = 2;
				setcolorchd(i);
			}
		}
	}
}