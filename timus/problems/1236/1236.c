#include "stdio.h"

int main(int argc, char* argv[])
{
    char line1[20001], line2[20003];
    unsigned int i = 0, x = 0, y = 0, key = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    gets(line1);
    gets(line2);

    key = line2[0] - ((line2[0] > 0x40) ? 0x37 : 0x30);
    key = key * 0x10 + line2[1] - ((line2[1] > 0x40) ? 0x37 : 0x30);

    key ^= 0x20;
    printf("%2X", key);
    for(i = 2; line2[i] != 0; i+=2){
        y = line2[i] - ((line2[i] > 0x40) ? 0x37 : 0x30);
        y = y * 0x10 + line2[i+1] - ((line2[i+1] > 0x40) ? 0x37 : 0x30);

        x = line1[i-2] - ((line1[i-2] > 0x40) ? 0x37 : 0x30);
        x = x * 0x10 + line1[i-1] - ((line1[i-1] > 0x40) ? 0x37 : 0x30);

        key ^= (x^y);
        printf("%02X", key);
    }

    return 0;
}
