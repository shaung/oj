#include "stdio.h"

int main(int argc, char* argv[])
{
    unsigned int x = 0, min = 0, fee = 0;
    unsigned int i = 0;
    double gold = 0.0, ratio = 0.0;

    scanf("%lu %lu %lu", &x, &min, &fee);

    gold = x;
    ratio = 1 - fee * 0.01;

    while(1){
        if(gold <= min) break;
        gold *= ratio;
        i++;
    }

    printf("%lu", i);
    
    return 0;
}
