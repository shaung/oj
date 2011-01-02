#include "stdio.h"

#define NMAX 7500
#define NODE 1
#define LEAF 0

short n = 0;

char leafs[NMAX + 1] = {0}; /* candicates */

short get_leaf(){
    short i;
    for(i = 1; i <= n; i++){
        if(leafs[i] == LEAF)
            return i;
    }
    return -1;
}

int main(int argc, char* argv[])
{
    short pruf[NMAX+1] = {0};       /* input */
    short father[NMAX+1] = {0};     /* connection */
    short last[NMAX+1] = {0};       /* last position of a pruf node indicates when it will turns into a leaf */
    short i = 0, j = 0;
    short node, leaf;

    while(scanf("%hd[ \n]", &pruf[++n]) == 1){
        leafs[pruf[n]] = NODE;
        last[pruf[n]] = n;
    }

    for (i = 1; i < n; i++){
        node = pruf[i];
        leaf = get_leaf();
        if(leaf == -1)
            break;
        father[leaf] = node;
        leafs[leaf] = -1;
        if(last[node] == i)
            leafs[node] = LEAF;
    }

    for(i = 1; i <= n; i++){
        printf("%hd:", i);
        for(j = 1; j <= n; j++){
            if(father[j] == i || father[i] == j){
                printf(" %hd", j);
            }
        }
        printf("\n");
    }

    return 0;
}

