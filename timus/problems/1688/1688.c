#include "stdio.h"

int main(){
    int n = 0, m = 0, x = 0, i = 0;
    long long sum = 0, goal = 0;

#ifndef ONLINE_JUDGE
    freopen("p1688.in", "rt", stdin);
    freopen("p1688.out", "wt", stdout);
#endif
    
    scanf("%d %d\n", &n, &m);
    goal = 3*(long long)n;
    for(i = 1; i <= m; i++){
        scanf("%d\n", &x);
        sum += x;
        if(sum > goal){
            printf("Free after %d times.", i);
            return 0;
        }
    }
    
    printf("Team.GOV!");
    
    return 0;
}