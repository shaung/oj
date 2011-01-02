#include "stdio.h"

int leap(int);

int main(int argc, char* argv[])
{
    int d = 0, m = 0, y = 0;
    int diff = 0, i = 0, j = 0, k = 0;
    int dinm[13] = {
        0,
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int weekmax = 0;
    int first = 0;

    scanf("%d %d %d", &d, &m, &y);

    if(y >= 2000){
        for(i = 2000; i < y; i++) diff += (365 + leap(i));
        for(j = 1; j < m; j++) diff += dinm[j];
        if(m > 2) diff += leap(y);
        first = (diff+5) % 7;
    } else {
        for(i = 1999; i > y; i--) diff += (365 + leap(i));
        for(j = m; j <= 12; j++) diff += dinm[j];
        if(m <= 2) diff += leap(y);
        first = 5 - diff% 7;
    }

    dinm[2] += leap(y);
    weekmax = (first + dinm[m]) / 7;
    if((first + dinm[m]) % 7 > 0) weekmax++;

    for(i = 0; i < 7 ;i++){
        switch(i){
        case 0: printf("mon"); break;
        case 1: printf("tue"); break;
        case 2: printf("wed"); break;
        case 3: printf("thu"); break;
        case 4: printf("fri"); break;
        case 5: printf("sat"); break;
        case 6: printf("sun"); break;
        }
        for(j = i+1 - first, k = 0; k < weekmax; j+=7, k++){
            if(j <= 0) printf("    ");
            else if(k == 0){
                if(j == d) printf(" [ %d", j);
                else  printf("   %d", j);
            }
            else if(j > dinm[m]) printf("     ");
            else if(j == d && k == 1){
                if(j < 10) printf("  [ %d", j);
                else printf("  [%d", j);
            }
            else if(j == d && k > 1){
                if(j < 10) printf(" [ %d", j);
                else printf("  [%d", j);
                if(j+7 > dinm[m])printf("]");
            }
            else if(j == d + 7){
                if(j < 10) printf("]   %d", j);
                else printf("]  %d", j);
            }
            else if(j < 10) printf("    %d", j);
            else printf("   %d", j);
        }
        printf("\n");
    }

	return 0;
}

int leap(int y){
    if(y%100 == 0) return (y%400==0) ? 1 : 0;
    else return (y%4 == 0) ? 1 : 0;
}