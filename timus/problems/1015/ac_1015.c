#include "stdio.h"
#include "string.h"

enum direction{ LEFT = 0, RIGHT = 1, FORWARD = 2, BACKWARD = 3, CLOCKWISE = 4};

struct dice{char l, r, t, fw, b, bw;};

void encode(char* line, struct dice *d);
void rotate_all(struct dice *p);
void rotate(struct dice *a, struct dice *b, char dir);

int main(int argc, char* argv[])
{
    struct dice v[30][24], dc;
    char vcnt = 0, code[100001] = {0};
    int n = 0, i = 0, j= 0, k = 0, found = 0;
    char line[11] = "";

    memset(v, 0, sizeof(v));

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d\n", &n);

    for(i = 0; i < n; i++){
        gets(line);
        encode(line, &dc);
        for(found = 0, j = 0; j < vcnt; j++){
            for(k = 0; k < 24; k++){
                if(memcmp(&dc, &v[j][k], sizeof(struct dice)) == 0){
                    code[i] = j+1;
                    found = 1;
                    break;
                }
            }
            if(found == 1) break;
        }
        if(code[i] == 0){
            memcpy(v[vcnt], &dc, sizeof(struct dice));
            rotate_all(v[vcnt]);
            /*
            printf("---------%d-------\n", vcnt);
            for(j = 0; j < 24; j++)
                printf("%d %d %d %d %d %d\n",
                    v[vcnt][j].l,
                    v[vcnt][j].r,
                    v[vcnt][j].t,
                    v[vcnt][j].fw,
                    v[vcnt][j].b,
                    v[vcnt][j].bw);
            */
            code[i] = ++vcnt;
        }
    }

    printf("%d\n", vcnt);
    for(i = 1; i <= vcnt; i++){
        for(found = 0, j = 0; j < n; j++){
            if(code[j] == i){
                found = 1;
                printf("%d ", j+1);
            }
        }
        if(found == 1) printf("\n");
    }

	return 0;
}

void encode(char* line, struct dice *d){
    /* 01234567890 */
    /* L R T F B B */
    /*         t w */
    d->l = line[0] - 0x30;
    d->r = line[2] - 0x30;
    d->t = line[4] - 0x30;
    d->fw = line[6] - 0x30;
    d->b = line[8] - 0x30;
    d->bw = line[10] - 0x30;
}

void rotate_all(struct dice *pd){
    struct dice *p = pd, *c = pd;

    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
    rotate(p, ++c, LEFT);
    p = c;
    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
    rotate(p, ++c, FORWARD);
    p = c;
    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
    rotate(p, ++c, LEFT);
    p = c;
    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
    rotate(p, ++c, FORWARD);
    p = c;
    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
    rotate(p, ++c, LEFT);
    p = c;
    rotate(p, ++c, CLOCKWISE);
    rotate(p+1, ++c, CLOCKWISE);
    rotate(p+2, ++c, CLOCKWISE);
}

void rotate(struct dice *a, struct dice *b, char dir){
    if(a == b) return;

    switch(dir){
    case LEFT:
        b->l = a->t;
        b->r = a->b;
        b->t = a->r;
        b->fw = a->fw;
        b->b = a->l;
        b->bw = a->bw;
        break;
    case RIGHT:
        b->l = a->b;
        b->r = a->t;
        b->t = a->l;
        b->fw = a->fw;
        b->b = a->r;
        b->bw = a->bw;
        break;
    case FORWARD:
        b->l = a->l;
        b->r = a->r;
        b->t = a->fw;
        b->fw = a->b;
        b->b = a->bw;
        b->bw = a->t;
        break;
    case BACKWARD:
        b->l = a->l;
        b->r = a->r;
        b->t = a->bw;
        b->fw = a->t;
        b->b = a->fw;
        b->bw = a->b;
        break;
    case CLOCKWISE:
        b->l = a->fw;
        b->r = a->bw;
        b->t = a->t;
        b->fw = a->r;
        b->b = a->b;
        b->bw = a->l;
        break;
    default:
        break;
    }
}
