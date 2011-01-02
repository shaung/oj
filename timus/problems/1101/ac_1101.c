#include "stdio.h"
#include "string.h"

#define IS_PM(x)   ((x) >= 'A' && (x) <= 'Z')
#define IS_CT(x)   ((x) == '1' || (x) == '0')
#define IS_OP(x)   ((x) == '!' || (x) == '&' || (x) == '|')
#define IS_QT(x)   ((x) == '(' || (x) == ')')

unsigned int reg = 0;

int reform(char *line){
	int i = 0;
	char *p = 0;

	for(i = 0, p = line; *p != 0; p++){
		if(*p == 'N' && *(p+1) == 'O' && *(p+2) == 'T'){
			*p = '!'; *(p+1) = ' '; *(p+2) = ' ';
			line[i++] = *p;
			p += 2;
		}
		else if(*p == 'A' && *(p+1) == 'N' && *(p+2) == 'D'){
			*p = '&'; *(p+1) = ' '; *(p+2) = ' ';
			line[i++] = *p;
			p += 2;
		}
		else if(*p == 'O' && *(p+1) == 'R'){
			*p = '|'; *(p+1) = ' '; *(p+2) = ' ';
			line[i++] = *p;
			p += 1;
		}
		else if(*p == 'T' && *(p+1) == 'R' && *(p+2) == 'U' && *(p+3) == 'E'){
			*p = '1'; *(p+1) = ' '; *(p+2) = ' '; *(p+3) = ' ';
			line[i++] = *p;
			p += 3;
		}
		else if(*p == 'F' && *(p+1) == 'A' && *(p+2) == 'L' && *(p+3) == 'S' && *(p+4) == 'E'){
			*p = '0'; *(p+1) = ' '; *(p+2) = ' '; *(p+3) = ' '; *(p+4) = ' ';
			line[i++] = *p;
			p += 4;
		} else if(*p != ' ') {
			line[i++] = *p;
		}
	}
	line[i] = 0;
	return i;
}

char exp[200] = "", szexp = 0;

void construct(char *line){
	char *p = 0, op[200] = "", pos = 0;

	for(p = line; *p != 0; p++){
		if(IS_OP(*p)){
			while(pos > 0){
				if(!IS_QT(op[pos-1]) && op[pos-1] < *p) exp[szexp++] = op[--pos];
				else break;
			}
			op[pos++] = *p;
		}
		else if(IS_CT(*p) || IS_PM(*p)) exp[szexp++] = *p;
		else if(*p == '(') op[pos++] = *p;
		else if(*p == ')'){
			while(op[pos-1] != '(')	exp[szexp++] = op[--pos];
			pos--;
		}
	}
	while(pos > 0) exp[szexp++] = op[--pos];
}

char get_reg(int a){
	return (reg & (1 << a)) > 0 ? 1 : 0;
}

void reverse_reg(int a){
	if((reg & (1 << a)) == 0) reg |= (1 << a);
	else reg &= ~(1 << a);
}

char eval(){
	char *p = 0, x[200] = "", pos = 0;
	for(p = exp + szexp - 1; ; p--){
		if(p >= exp){
			if(IS_OP(*p)) x[pos++] = *p;
			else if(IS_PM(*p)) x[pos++] = get_reg(*p - 0x40);
			else if(IS_CT(*p)) x[pos++] = *p - 0x30;
		}

		while(pos > 1){
			if(IS_OP(x[pos-1])) break;
			
			if(x[pos-2] == '!'){
				x[pos-2] = (x[pos-1] == 0) ? 1 : 0;
				pos -= 1;
				continue;
			}

			if(pos < 3) break;
			if(IS_OP(x[pos-3]) && !IS_OP(x[pos-2]) && !IS_OP(x[pos-1])){
				if(x[pos-3] == '&') x[pos-3] = x[pos-2] * x[pos-1];
				else if(x[pos-3] == '|') x[pos-3] = x[pos-2] + x[pos-1];
				x[pos-3] = (x[pos-3] > 0) ? 1 : 0;
				pos -= 2;
				continue;
			}
			break;
		}
		if(p < exp && pos == 1) break;
	}
	return x[0];
}

int main(){
	int n = 0, m = 0, k = 0, len = 0;
	int dx = 0, dy = 0, tx = 0, ty = 0;
	char line[300] = "", c = 0;
	char rip[202][202];
	int i = 0, x = 0, y = 0;

	memset(rip, 0, sizeof(rip));

#ifndef ONLINE_JUDGE
	freopen("input.txt", "rt", stdin);
	freopen("output.txt", "wt", stdout);
#endif

	gets(line);
	len = reform(line);
	//printf("%s\n", line);
	construct(line);
	//printf("%s\n", exp);

	scanf("%d %d %d\n", &n, &m, &k);
	for(i = 0; i < m; i++){
		scanf("%d %d\n", &x, &y);
		x += n; y += n;
		rip[x][y] = -1;
	}
	for(i = 0; i < k; i++){
		scanf("%d %d %c\n", &x, &y, &c);
		x += n; y += n;
		rip[x][y] = c - 0x40;
	}

	x = n; y = n;
	dx = 1; dy = 0;
	while(1){
		if(x < 0 || x > 2*n || y < 0 || y > 2*n) break;
		printf("%d %d\n", x-n, y-n);

		/* fork */
		if(rip[x][y] == -1){
			tx = dx; ty = dy;
			if(eval()){
				/* right */
				dx = (dx == 0) ? ty : 0;
				dy = (dy == 0) ? -1*tx : 0;
			} else {
				/* left */
				dx = (dx == 0) ? -1*ty : 0;
				dy = (dy == 0) ? tx : 0;
			}
		}
		/* rip */
		else if(rip[x][y] != 0) reverse_reg(rip[x][y]);

		x += dx; y += dy;
	}

	return 0;
}