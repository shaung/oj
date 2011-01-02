#include "stdio.h"
#include "string.h"

#define IS_DIGIT(x) ((x >= 0x30) && (x <= 0x39))
#define IS_SIGN(x)  ((x == '+') || (x == '-'))
#define IS_EXP(x)   ((x == 'e') || (x == 'E'))
#define OVERFLOW(x) (((x) > 200) || ((x) < -200))

/* <sign><0-9><.><0-9><e><sign><0-9> */
/* +001.001000000e+00000000 */
#define EP_SIGN_INT_PUNC    0
#define EP_INT_PUNC         1
#define EP_INT_PUNC_E_BREAK 2
#define EP_DEC              3
#define EP_DEC_E_BREAK      4
#define EP_SIGNE_INTE       5
#define EP_INTE             6
#define EP_INTE_BREAK       7

struct number{
	char sign, dec[201], lendec;
	short e;
};

int main(int argc, char* argv[])
{
	struct number num;
	int n = 0, i = 0, ep = 0, eplus = 0, shouldcnt = 0, esign = 0, etmp = 0, err = 0;
	char line[101] = "", c = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

	while(gets(line) != NULL){
		if(line[0] == '#' && line[1] == 0) break;

		memset(&num, 0, sizeof(num));
		memset(num.dec, 0x30, sizeof(num.dec) - 1);
		err = 0;
		eplus = 1;
		ep = EP_SIGN_INT_PUNC;
		for(i = 0; ; i++){
			c = line[i];
			if(ep == EP_SIGN_INT_PUNC){
				if(IS_SIGN(c)){
					num.sign = (c == '-') ? 0 : 1;
					ep = EP_INT_PUNC;
				} else if(IS_DIGIT(c)){
					num.sign = 1;
					if(c > 0x30){
						num.dec[num.lendec++] = c;
						if(eplus == 1) num.e++;
					}
					ep = EP_INT_PUNC_E_BREAK;
				} else if(c == '.'){
					num.sign = 1;
					eplus = 0;
					ep = EP_DEC;
				} else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_INT_PUNC){
				if(IS_DIGIT(c)){
					if(num.lendec > 0 || c > 0x30){
						num.dec[num.lendec++] = c;
						if(eplus == 1) num.e++;
					}
                    ep = EP_INT_PUNC_E_BREAK;
				} else if(c == '.'){
					eplus = 0;
					ep = EP_DEC;
				} else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_INT_PUNC_E_BREAK){
				if(IS_DIGIT(c)){
					if(num.lendec > 0 || c > 0x30){
						num.dec[num.lendec++] = c;
						if(eplus == 1) num.e++;
					}
					ep = EP_INT_PUNC_E_BREAK;
				} else if(c == '.'){
					eplus = 0;
					ep = EP_DEC;
				} else if(IS_EXP(c)){
                    eplus = 0;
					ep = EP_SIGNE_INTE;
				} else if(c == 0) break;
				else {
					err = 1;
					break;
				}
			}
            /* when dealing with the fractional part, should be care of sth. like 0.001001000 and 0.1000 */
            /* fractional part the first digit */
			else if(ep == EP_DEC){
				if(IS_DIGIT(c)){
                    if(c == 0x30) eplus++;
                    else num.dec[num.lendec++] = c;
                    shouldcnt = (c == 0x30) ? 0 : 1;
					ep = EP_DEC_E_BREAK;
				} else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_DEC_E_BREAK){
				if(IS_DIGIT(c)){
                    if(c == 0x30) eplus++;
                    else {
                        //num.lendec++;
                        if(shouldcnt == 0){
                            shouldcnt = 1;
                            if(num.lendec == 0) num.e -= eplus;
                            else num.lendec += eplus;
                        }
                        else {
                            num.lendec += eplus;
                        }
  						num.dec[num.lendec] = c;
                        if(num.lendec == 0) num.lendec++;
                        eplus = 1;
                    }
					ep = EP_DEC_E_BREAK;
				} else if(IS_EXP(c)){
					ep = EP_SIGNE_INTE;
				} else if(c == 0) break;
				else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_SIGNE_INTE){
				if(IS_SIGN(c)){
					esign = (c == '-') ? -1 : 1;
					etmp = 0;
					ep = EP_INTE;
				} else if(IS_DIGIT(c)){
					esign = 1;
					etmp = c - 0x30;
					ep = EP_INTE_BREAK;
				} else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_INTE){
				if(IS_DIGIT(c)){
					if(!OVERFLOW(num.e + (etmp * esign)))
						etmp = etmp * 10 + c - 0x30;
					ep = EP_INTE_BREAK;
				}
                else {
					err = 1;
					break;
				}
			}
			else if(ep == EP_INTE_BREAK){
				if(IS_DIGIT(c)){
					if(!OVERFLOW(num.e + (etmp * esign)))
						etmp = etmp * 10 + c - 0x30;
					ep = EP_INTE_BREAK;
				} else if(c == 0){
					num.e += (etmp * esign);
					break;
				}
				else {
					err = 1;
					break;
				}
			}
			else break;
		}

		scanf("%d", &n);
        gets(line);

        /*		
		printf("[%s] ->\n", line);
		if(num.sign == 0) printf("-");
		printf(" 0.%se%d\n", num.dec, num.e);
        */
        if(err == 1) printf("Not a floating point number\n");
		else{
			if(num.lendec == 0) num.e = 0;
			/* sign when rslt != 0 */
			if(num.sign == 0 && num.lendec > 0 && n + num.e > 0) printf("-");
			/* int part */
			if(num.e <= 0) printf("0");
			else for(i = 0; i < num.e; i++) printf("%c", num.dec[i]);
			/* fractional part */
			if(n > 0){
				printf(".");
				/* anyway we need to output n digits here */
				if(num.e >= 0) for(i = 0; i < n; i++) printf("%c", num.dec[num.e + i]);
				else {
					num.e *= -1;
 				    for(i = 0; i < num.e && i < n; i++) printf("0");
					for(i = 0; i < n - num.e; i++) printf("%c", num.dec[i]);
				}
			}
			printf("\n");
		}
	}

	return 0;
}
