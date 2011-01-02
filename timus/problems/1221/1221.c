#include "stdio.h"
#include "string.h"

#define OFFLINE

int main(int argc, char* argv[])
{
	struct block{char start, length, level;};
	int len, i, j, k;
	int rslt;
	char line[201];
	struct block hope[50], hope2[50];
	int size = 0, size2 = 0;
	int progress = -1; /* -1:start 0:counting-one 1: conting-zero 2:conting-one */
	int s = 0, z = 0, e = 0;
	int fail = 0;
	int addtive = 0;

	memset(line, 0, sizeof(line));
	memset(hope, 0, sizeof(hope));

#ifndef ONLINE_JUDGE
   freopen("input.txt", "rt", stdin);
   freopen("output.txt", "wt", stdout);
#endif

	/* calculate the patterns */
	while(scanf("%d", &len)){
		if(len==0)break;
		gets(line);

		memset(hope, 0, sizeof(hope));
		size = 0;
		rslt = 0;

		for(i = 0; i < len; i++){
			gets(line);
			if(len < 3)continue;

			memset(hope2, 0, sizeof(hope2));
			size2 = 0;
			progress = -1;
			s = 0;
			z = 0;
			e = 0;

			/* seek hopes */
			for(j = 0; j < len; j++){
				if(line[2 * j] == 0x30){
					/* 0 */
					switch(progress){
					case 0:
						z = j;
						progress = 1;
						break;
					case 1:
						if(z > 0){
							s = 0;
							z = 0;
							e = 0;
							progress = -1;
						}
						break;
					case 2:
						//e = j - 1;
						/* save */
						if((e-z) > (z-s)){
							e -= e-z-z+s;
						} else {
							s += z-s-e+z;
						}
						for(k = 0; k < z - s; k++){
							hope2[size2].start = s + k;
							hope2[size2].length = e-s+1 - 2 * k;
							hope2[size2].level = hope2[size2].length - 1;
							size2++;
						}
						s = z + 1;
						z = j;
						e = 0;
						progress = 1;
						break;
					default:
						break;
					}
				} else { /* 1 */
					switch(progress){
					case -1:
						s = j;
						progress = 0;
						break;
					case 1:
						e = j;
						progress = 2;
						break;
					case 2:
						e = j;
						break;
					default:
						break;
					}
				}
				if(j == len - 1){
					if(progress == 2 && e > 0){
						/* save */
						if((e-z) > (z-s)){
							e -= e-z-z+s;
						} else {
							s += z-s-e+z;
						}
						for(k = 0; k < z - s; k++){
							hope2[size2].start = s + k;
							hope2[size2].length = e-s+1 - 2 * k;
							hope2[size2].level = hope2[size2].length - 1;
							size2++;
						}
						progress = 0;
					}
					break;
				}
			}
#ifndef OFFLINE
			printf("--hope2(%d)\n", i);
			for(j = 0; j < size2; j++){
				printf("%d, start=%d, length = %d, level = %d\n", j, hope2[j].start, hope2[j].length, hope2[j].level);
			}
#endif
			/* calculate level of hopes */
			for(k = 0; k < size;){
				fail = 0;
				z = hope[k].start + (hope[k].length-1)/2;
				
				if(2*hope[k].level + 1 > hope[k].length){
					addtive = hope[k].length - hope[k].level;
				} else {
					addtive = hope[k].level - 1;
				}

				for(j=hope[k].start; j < (z - addtive); j++){
					if(line[2*j] != 0x31){
						fail = 1;
						break;
					}
				}
				if(fail == 0){
					for(j = z - addtive; j < (z + addtive + 1); j++){
						if(line[2*j] != 0x30){
							fail = 1;
							break;
						}
					}
				}
				if(fail == 0){
					for(j = z + addtive + 1; j < hope[k].start + hope[k].length; j++){
						if(line[2*j] != 0x31){
							fail = 1;
							break;
						}
					}
				}
				if(fail>0){
					if(hope[k].level + 1 == hope[k].length && hope[k].length > 3){
						hope[k].start++;
						hope[k].length -= 2;
						hope[k].level -= 2;
					} else {
						memcpy(&hope[k], &hope[--size], sizeof(struct block));
					}
					continue;
				}

				hope[k].level--;
				/* hope comes true */
				if(hope[k].level <= 0){
					if(rslt < hope[k].length)rslt = hope[k].length;
					memcpy(&hope[k], &hope[--size], sizeof(struct block));
					continue;
				}
				k++;
			}

			for(k = 0; k < size;){
				if(hope[k].length <= rslt){
					memcpy(&hope[k], &hope[--size], sizeof(struct block));
					continue;
				} 
				k++;
			}

			for(j = 0; j < size2; j++){
				if(hope2[j].length <= rslt)continue;
				memcpy(&hope[size++], &hope2[j], sizeof(struct block));
			}

#ifndef OFFLINE
			printf("----hope(%d)\n", i);
			for(j = 0; j < size; j++){
				printf("%d, start=%d, length = %d, level = %d\n------------------\n", j, hope[j].start, hope[j].length, hope[j].level);
			}
#endif
		}

		if(rslt == 0){
			printf("No solution\n");
		} else {
			printf("%d\n", rslt);
		}
	}
	
	return 0;
}

