#include "stdio.h"
#include "string.h"

char v[2000][4000], tmp[4000] = "";

void add(char *rslt, char *a, char *b);
int multiply(char *rslt, char *a, char *b);

int main(int argc, char* argv[])
{
    int n = 0, k = 0, i = 0, len = 0;

    memset(v, 0, sizeof(v));

    scanf("%d %d", &n, &k);

    v[0][0] = 0x31;
    v[1][0] = k-1 + 0x30;
    for(i = 2; i <= n; i++){
        add(tmp, v[i-1], v[i-2]);
        len = multiply(v[i], tmp, v[1]);
    } 

    while(v[n][len] == 0x30) len--;
    for(i = len; i >= 0; i--){
        printf("%c", v[n][i]);
    }

	return 0;
}

void add(char *rslt, char *a, char *b){
    short i = 0, j = 0;
    char sum = 0, rem = 0;
    for(i = 0; ; i++){
        sum = a[i] + b[i] + rem;
        if(a[i] != 0 && b[i] != 0) sum -= 0x60;
        else if(a[i] == 0 && b[i] == 0) {
            rslt[i] = rem + 0x30;
            break;
        } else sum -= 0x30;
        
        if(sum > 10){
            sum -= 10;
            rem = 1;
        } else rem = 0;
        rslt[i] = sum + 0x30;
    }
}

int multiply(char *rslt, char *a, char *b){
    int i = 0, j = 0, product = 0, rem = 0, len = 0;
    for(i = 0; a[i] != 0; i++){
        rem = 0;
        for(j = 0; ; j++){
            if(len < i+j) len = i+j;
            if(b[j] != 0){
                product = (a[i] - 0x30) * (b[j] - 0x30) + rem;
                if(product > 10){
                    rem = product / 10;
                    product %= 10;
                } else rem = 0;
                rslt[i+j] += product;
                if(rslt[i+j] >= 10){
                    rem += rslt[i+j] / 10;
                    rslt[i+j] %= 10;
                }
            }
            else {
                rslt[i+j] += rem;
                if(rslt[i+j] >= 10){
                    rslt[i+j+1] = rslt[i+j] / 10;
                    rslt[i+j] %= 10;
                }
                break;
            }
        }
    }
    for(i = 0; i <= len; i++) rslt[i] += 0x30;
    return len;
}