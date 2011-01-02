#include "stdio.h"
#include "string.h"

int main(){
    char line[10001] = "", rslt[81] = "";
    int pos=0;
    int i = 0;

    memset(rslt, ' ', 80);
    rslt[80] = 0;

    fgets(line, 10001, stdin);
    for(i = 0; line[i] != '\n' && line[i] != 0; i++){
        char c = line[i];
        if(c == '<'){
            if(pos > 0) pos--;
        } else {
            if(c != '>'){
                rslt[pos] = c;
            }
            if(++pos >= 80) pos=0;
        }
    }
    for(i = 0; i < 80; i++){
        printf("%c", rslt[i]);
    }

    return 0;
}

