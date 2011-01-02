#include "stdio.h"
#include "string.h"

int main(int argc, char* argv[])
{
	int len = 0, n = 0;
	char line[21];
	unsigned short s[100000][3];
	unsigned int index, value;
	unsigned int i = 0, lastpos[1001];

	scanf("%d", &len);

	memset(line, 0, sizeof(line));
	memset(s, 0, sizeof(s));
	memset(lastpos, 0, sizeof(lastpos));

	while(gets(line)){
		if(len-- < 0)break;
		if(*line == 0)continue;

		if(line[3] == ' '){
			/* POP */
			index = 0;
			for(i=4;line[i]!=0;i++){
				index = index*10 + (line[i]-0x30);
			}
			i = lastpos[index];
			lastpos[index] = s[i][2] + ((s[i][1] & 0x8000) << 1);
			printf("%u\n", s[i][0] + ((s[i][1] & 0x7FFF) << 16));
		} else{
			/* PUSH */
			index = 0;
			for(i=5;line[i]!=0x20;i++){
				index = index*10 + (line[i]-0x30);
			}
  		    value = 0;
			for(i++;line[i]!=0;i++){
				value = value*10 + (line[i]-0x30);
			}
			i = lastpos[index];
			s[n][2] = i & 0xFFFF;
			s[n][1] = ((unsigned)(i & 0x10000) >> 1) + (value >> 16);
			s[n][0] = value & 0xFFFF;
		    lastpos[index] = n++;
		}
	}

	return 0;
}
