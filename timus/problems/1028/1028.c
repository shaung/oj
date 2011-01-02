#include "stdio.h"
#include "string.h"

int findstar(int*, int);

int main(int argc, char* argv[])
{
	int n = 0, level[15001], stars[15001], y = 0;
	char line[13];
	int i = 0, j = 0;

	memset(level, 0, sizeof(level));
	memset(stars, 0, sizeof(stars));

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	for(i = 0; i < n; i++){
		gets(line);

		for(stars[i] = 0, j = 0; line[j] != 0x20 && line[j] != 0; j++)
			stars[i] = stars[i] * 10 + line[j] - 0x30;

		if((i == 0) || (i > 0 && stars[i] >= stars[i-1])) y = i;
		else{
			y = findstar(stars, i);
		}

		level[y]++;
	}

	for(i = 0; i < n; i++){
		printf("%d\n", level[i]);
	}

	return 0;
}

int findstar(int* stars, int item){
	int size = item;
	int tmp = stars[item];
	int i = 0, prev = 0, prev2 = item;

	for(i = (prev + prev2)/2;
	    prev2 - prev > 1;
		i = (prev + prev2)/2){

		if(stars[item] > stars[i]) prev = i + 1; /* need to move backward */
		else if(stars[item] < stars[i]) prev2 = i;
		else prev = i;
	}

	while(prev2 > 0 && stars[prev2 - 1] > stars[item]) prev2--;
	memcpy(stars + prev2 + 1, stars + prev2, sizeof(int) * (item-prev2));
	stars[prev2] = tmp;

	return prev2;
}
