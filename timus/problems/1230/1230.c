#include "stdio.h"

int main(int argc, char* argv[])
{
#ifndef ONLINE_JUDGE
    freopen("output.txt", "wt", stdout);
#endif

    printf("B=\"';A=\";A='\"?B=+$(A,1,1)+$(B,1,4)+$(A,1,1)+$(B,2,3)+$(B,1,1)+$(A,1,125)+$(B,1,1)+$(B,2,1)+$(A,2,1)+$(B,1,1)+$(A,3,2)+$(B,1,1)+$(A,5,121)';?'B='+$(A,1,1)+$(B,1,4)+$(A,1,1)+$(B,2,3)+$(B,1,1)+$(A,1,125)+$(B,1,1)+$(B,2,1)+$(A,2,1)+$(B,1,1)+$(A,3,2)+$(B,1,1)+$(A,5,121)");

	return 0;
}
