#include "stdio.h"
#include "string.h"

/*
 1.Any (but only one) symbol 0 is replaced by 1. 
 2.Any (but only one) symbol is removed. 
 3.A symbol (0 or 1) is inserted at any position. 
*/
int main(int argc, char* argv[])
{
	int n = 0, sum = 0, len = 0, i = 0, j = 0;
	char line[1003] = {0}, rslt[1003] = {0};
	short next[1003] = {0};


#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	scanf("%d\n", &n);

	while(gets(&line[1]) != NULL){
		if(line[1] == 0) continue;

		len = 0;
		sum = 0;
		memset(next, 0 ,sizeof(next));
		memset(rslt, 0 ,sizeof(rslt));
		for(i = 1; line[i] != 0; i++){
			if(line[i] == 0x31)	sum += i;
			if(line[i] == 0x30 || line[i] == 0x31){
				rslt[++len] = line[i];
			}
		}

		if(len == n && sum % (n+1) == 0){
			printf("%s\n", rslt+1);
			continue;
		}

		for(i = len; i >= 1; i--){
			if(rslt[i] == 0x31) next[i-1] = next[i] + 1;
			else next[i-1] = next[i];
		}

		if(len == n){
			/* need to change 1 to 0 somewhere : this will decrease the sum */
			for(i = 1; i <= len; i++){
				if(rslt[i] == 0x31 && ((sum - i) % (n+1) == 0)){
					rslt[i] = 0x30;
					printf("%s", rslt+1);
					break;
				}
			}
		}
		else if(len > n){
			for(i = 1; i <= len; i++){
				/* need to delete a 0 somewhere : this will decrease the sum by next[i] */
				if(((rslt[i] == 0x30) && ((sum - next[i]) % (n+1) == 0)) ||
				/* need to delete a 1 somewhere : this will decrease the sum by next[i] + i */
				   ((rslt[i] == 0x31) && ((sum - next[i] - i) % (n+1) == 0))){
					for(j = 1; j < i; j++) printf("%c", rslt[j]);
					for(j = i+1; j <= len; j++) printf("%c", rslt[j]);
					break;
				}
			}
		} else if(len < n){
			rslt[n] = 0x30;
			for(i = 0; i <= len; i++){
				/* inserting a 0 after i will cause the sum increase by next[i] */
				if((sum + next[i]) % (n+1) == 0){
					for(j = 1; j <= i; j++) printf("%c", rslt[j]);
					printf("0");
					for(j = i+1; j <= len; j++) printf("%c", rslt[j]);
					break;
				}
				/* inserting a 1 after i will cause the sum increase by next[i] + i + 1 */
				else if((sum + next[i] + i + 1) % (n+1) == 0){
					for(j = 1; j <= i; j++) printf("%c", rslt[j]);
					printf("1");
					for(j = i+1; j <= len; j++) printf("%c", rslt[j]);
					break;
				}
			}
		}
		printf("\n");
	}

	return 0;
}
