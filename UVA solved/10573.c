#include<stdio.h>
#include<math.h>

int main()
{
    int r1, r2, t, test;
    char ch;
    double pi=2*acos(0);
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%d", &t);
        ch=getchar();
        if(ch!='\n')
        {
            scanf("%d", &r2);
            r1=t;
            printf("%.4lf\n", 2*pi*r1*r2);
        }
        else printf("%.4lf\n", pi/8*t*t);
    }
    return 0;
}
