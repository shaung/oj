#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
	int block[30001];
	int i = 0, time = 0, request = 0;
	char line[50] = "";

	memset(block, -1, sizeof(block));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	while(gets(line) != NULL){
		for(time = 0, i = 0; line[i] != 0; i++){
			if(line[i] < 0x30 || line[i] > 0x39) break;
			time = time * 10 + line[i] - 0x30;
		}
		while(line[i] == 0x20) i++;
		if(line[i] == '+'){
			/* find the min free block number */
			for(i = 1; i <= 30000; i++){
				if(block[i] < 0 || block[i] <= time - 600){
					block[i] = time;
					printf("%d\n", i);
					break;
				}
			}
		}
		else if(line[i] == '.'){
			while(line[++i] == 0x20);
			for(request = 0; line[i] != 0x20 && line[i] != 0; i++){
				request = request * 10 + line[i] - 0x30;
			}

			if(block[request] >= 0 && (time - block[request] < 600)){
				/* OK */
				block[request] = time;
				printf("+\n");
			} else {
				/* NG */
				block[request] = -1;
				printf("-\n");
			}
		}
	}


	return 0;
}
