#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    struct jedi{
        char name[31];
        int a, b, c;
    };

    struct jedi jd[200];
    char g[200][200];
    int n = 0;
    int i = 0, j = 0, k = 0;

    memset(jd, 0, sizeof(jd));
    memset(g, 0, sizeof(g));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        scanf("%s %d %d %d\n", jd[i].name, &(jd[i].a), &(jd[i].b), &(jd[i].c));
    }

    if(n == 1){
        printf("%s\n", jd[0].name);
        return 0;
    }

    /* construct the oriented graph: j -> i means i can beat j */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(i == j) continue;
            if((jd[i].a > jd[j].a && jd[i].b > jd[j].b) ||
               (jd[i].a > jd[j].a && jd[i].c > jd[j].c) ||
               (jd[i].b > jd[j].b && jd[i].c > jd[j].c)){
                g[j][i] = 1;
            }
        }
    }

    /* put all the j->i to true if they are connected */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(g[j][i] == 1){
                for(k = 0; k < n; k++){
                    if(k == j || k == i) continue;
                    if(g[i][k] == 1) g[j][k] = 1;
                }
            }
        }
    }

    /* find all one-way connectivities */
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            /* if i can beat j but j cannot beat i than j loses */
            if(g[j][i] == 1 && g[i][j] != 1){
                for(k = 0; k < n; k++){
                    g[k][j] = 0;
                }
            }
        }
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(g[j][i] == 1){
                printf("%s\n", jd[i].name);
                break;
            }
        }
    }

	return 0;
}
