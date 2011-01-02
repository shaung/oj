#include "stdio.h"

int main(int argc, char* argv[])
{
    int n = 0, p[1001] = {0};
    __int64 i = 0, j = 0, k = 0, tmp = 0, m[1001] = {0};

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
//    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(i = 1; i <= n; i++) scanf("%d ", &p[i]);

    for(i = 1; i <= n; i++){
        tmp = i;
        do{
          tmp = p[tmp];
          m[i]++;
        } while(tmp != i);
    }

    for(i = n; i >= 1; i--){
        for(j = 1; j < i; j++){
            if(m[j] < m[j+1]){
                tmp = m[j];
                m[j] = m[j+1];
                m[j+1] = tmp;
            }
        }
    }

    for(i = 1; i < n; i++){
        j = m[i];
        k = m[i+1];
        tmp = j%k;
        while(tmp != 0){
            j = k;
            k = tmp;
            tmp = j%k;
        }
        m[i+1] /= k;
        m[i+1] *= m[i];
    }

    printf("%d", m[n]);

    return 0;
}
