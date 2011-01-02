#include "stdio.h"
#include "math.h"

int main(int argc, char* argv[])
{
    int ax = 0, ay = 0, bx = 0, by = 0, cx = 0, cy = 0;
    double ab2 = 0, bc2 = 0, ac2 = 0, ac = 0;
    double oa = 0, ob = 0, oc = 0, ob2 = 0, oc2 = 0;
    double rax = 0, ray = 0, rbx = 0, rby = 0, rcx = 0, rcy = 0;
    int i = 0;

#ifndef ONLINE_JUDGE
    freopen("input.txt", "rt", stdin);
    freopen("output.txt", "wt", stdout);
#endif

    scanf("%d %d\n", &ax, &ay);
    scanf("%d %d\n", &bx, &by);
    scanf("%d %d\n", &cx, &cy);

    /* AB > BC -> AB^2 > BC^2*/
    ab2 = (bx-ax)*(bx-ax) + (by-ay)*(by-ay);
    bc2 = (cy-by)*(cy-by) + (cx-bx)*(cx-bx);
    ac2 = (cx-ax)*(cx-ax) + (cy-ay)*(cy-ay);
    if(ab2 > bc2 && ab2 != (bc2 + ac2)){
        printf("NO\n");
        oc2 = (ac2 - ab2 + bc2)*(ac2 - ab2 + bc2) / (4*ac2);
        ob2 = bc2- oc2;

        rax = 0.0 - sqrt(ab2 - ob2);
        ray = 0;
        rbx = 0;
        rby = 0.0 - sqrt(ob2);
        rcx = sqrt(oc2);
        rcy = 0;

        printf("%.11f %.11f\n", rax, ray); /* A */
        printf("%.11f %.11f\n", rbx, rby); /* B */
        printf("%.11f %.11f\n", rcx, rcy); /* C */


    } else
        printf("YES\n");

	return 0;
}
