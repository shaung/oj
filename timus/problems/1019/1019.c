#include "stdio.h"
#include "string.h"

#define MAX_INT 1000000000

struct segment{int start, end;};
struct segment v[20000];
char removed[20000] = "";
int vsize = 0;

int main(int argc, char* argv[])
{
    int n = 0, i = 0, j = 0, s = 0, e = 0, found = 0;
    char color = 0;
    struct segment max;
    memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);
    v[vsize].start = 0;
    v[vsize].end = MAX_INT - 1;
    vsize++;
    for(i = 0; i < n; i++){
        scanf("%d %d %c\n", &s, &e, &color);
        if(s >= e) continue;
        e--;
        if(color == 'b'){
            for(j = 0; j < vsize; j++){
                if(removed[j] == 1 || v[j].start > e || v[j].end < s) continue;
                /* ------b */
                /*  ---j   */
                if(v[j].start >= s && v[j].end <= e){
                    removed[j] = 1;
                }
                /* insection */
                else if(v[j].start <= e && v[j].end >= s){
                    if(v[j].start < s && v[j].end > e){
                        removed[j] = 1;
                        v[vsize].start = v[j].start;
                        v[vsize].end = s - 1;
                        vsize++;
                        v[vsize].start = e + 1;
                        v[vsize].end = v[j].end;
                        vsize++;
                    }
                    if(v[j].start < s && v[j].end <= e){
                        v[j].end = s - 1;
                    }
                    if(v[j].start >= s && v[j].end > e){
                        v[j].start = e + 1;
                    }
                }
            }
        }
        else if(color == 'w'){
            for(found = 0, j = 0; j < vsize; j++){
                if(removed[j] == 1 || v[j].start > e+1 || v[j].end < s-1) continue;
                /* ------w */
                /*  ---j   */
                if(v[j].start == s && v[j].end == e){
                    found = 1;
                    break;
                } else if(v[j].start >= s && v[j].end <= e){
                    v[j].start = s;
                    v[j].end = e;
                    found = 1;
                } else if(v[j].start <= s && v[j].end >= e){
                    found = 1;
                    break;
                }
                if(v[j].end == s - 1){
                    v[j].end = e;
                    s = v[j].start;
                    found = 1;
                }
                if(v[j].start == e + 1){
                    v[j].start = s;
                    e = v[j].end;
                    found = 1;
                }
                /* insection */
                if(v[j].start <= e && v[j].end >= s){
                    found = 1;
                    if(v[j].start > s) v[j].start = s;
                    if(v[j].end < e) v[j].end = e;
                    s = v[j].start;
                    e = v[j].end;
                }
            }
            if(found == 0){
                v[vsize].start = s;
                v[vsize].end = e;
                vsize++;
            }
        }
    }

    max.start = 0;
    max.end = -1;
    for(i = 0 ; i < vsize; i++){
        if(removed[i] == 1) continue;
        if(v[i].end - v[i].start > max.end - max.start){
            max.start = v[i].start;
            max.end = v[i].end;
        }
    }

    printf("%d %d", max.start, max.end+1);

	return 0;
}
