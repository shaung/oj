#include "stdio.h"
#include "string.h"

void calc(char* result, char* num);

int main(int argc, char* argv[])
{
	unsigned int in = 0, rslt = 0;
	int d = 0, r = 0;
	int i = 0;
	char result[500];
	char C_Value[21][11] = {
	    /*  0 */	"1",
	    /*  1 */	"3",
	    /*  2 */    "9",
		/*  3 */    "27",
		/*  4 */    "81",
		/*  5 */    "243",
		/*  6 */    "729",
		/*  7 */    "2187",
		/*  8 */    "6561",
		/*  9 */    "19683",
		/* 10 */    "59049",
		/* 11 */    "177147",
		/* 12 */    "531441",
		/* 13 */    "1594323",
		/* 14 */    "4782969",
		/* 15 */    "14348907",
		/* 16 */    "43046721",
		/* 17 */    "129140163",
		/* 18 */    "387420489",
		/* 19 */    "1162261467",
		""
	};

	scanf("%d", &in);

	if(in <= 4){
		rslt = in;
		printf("%d", rslt);
		return 0;
	} else {
		d = in/3;
		r = in%3;
		if(r<2){
			d--;
			r+=3;
		}

		if(d < 19){
			/* small enough for calculating */
			rslt = r;
			for(i = 0; i <d; i++){
				rslt *=3;
			}
			printf("%d", rslt);
			return 0;
		} else {
			/* result bigger than 32-bit(2*3^19) */
			memset(result, 0, sizeof(result));
			sprintf(result, "%d", r);
			r = d % 19;
			d = d / 19;
			if(r > 0)
				calc(result, C_Value[r]);
			for(i = 0; i < d; i++){
				calc(result, C_Value[19]);
			}
			printf("%s\n", result);
			return 0;
		}
	}

	return 0;
}


void calc(char* result, char* num2){
	int size1, size2;
	char num1[500] = "";
	char buffer[500];
	int i = 0, j = 0, pos = 0;
	int tmp = 0, tmp2 = 0, tmpb = 0;

	memset(buffer, 0x30, sizeof(buffer) - 1);
	buffer[499] = 0;

	size1 = strlen(result);
	memcpy(num1, result, size1);

	size2 = strlen(num2);

	for(i = size1 - 1; i >= 0; i--){
		pos = size1 - i - 1;
		tmp = tmpb = tmp2 = 0;
		for(j = size2 - 1; j >= 0; j--){
			tmp = (num2[j]-0x30) * (num1[i] - 0x30);
			tmpb = buffer[pos] - 0x30;
			buffer[pos++] = ((tmp+tmpb+tmp2)%10) + 0x30;
			tmp2 = (tmp+tmpb+tmp2)/10;
		}
		buffer[pos++] = (tmp2) + 0x30;
	}

	while(buffer[pos] == 0x30)pos--;

	memset(result, 0, sizeof(result));
	for(i = pos; i >= 0; i--){
		result[pos - i] = buffer[i];
	}

	return;
}
