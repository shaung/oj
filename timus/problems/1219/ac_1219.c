#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
    int i = 0, j = 0, prev = -1, prev2 = -1;
    int cnt1[26];
    int cnt2[26][26];
    int cnt3[26][26][26];

    memset(cnt1, 0, sizeof(cnt1));
    memset(cnt2, 0, sizeof(cnt2));
    memset(cnt3, 0, sizeof(cnt3));

#ifndef ONLINE_JUDGE
    freopen("output.txt", "wt", stdout);
#endif

    for(i = 0; i < 1000000; i++){
        j =  (i%2 == 0) ? 0 : 25;
        while(j >= 0 && j < 26){
            if(cnt1[j] == 39999) ;
            else if(prev >= 0 && cnt2[prev][j] == 1999) ;
            else if(prev >= 0 && prev2 >= 0 && cnt3[prev2][prev][j] == 99) ;
            else if(j == prev || j == prev2) ;
            else{
                printf("%c", j + 97);
                cnt1[j]++;
                if(prev >= 0)
                    cnt2[prev][j]++;
                if(prev >= 0 && prev2 >= 0)
                    cnt3[prev2][prev][j]++;

                prev2 = prev;
                prev = j;
                break;
            }
            if(i%2 == 0) j++; else j--;
        }
    }

    return 0;
}
