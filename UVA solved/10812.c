#include<stdio.h>

int main()
{
    unsigned long n, i, s, d;
    long x, y;
    scanf("%lu", &n);
    for(i=0;i<n;i++)
    {
        scanf("%lu%lu", &s, &d);
        x=(s+d)/2;
        y=s-x;
        if(x>=0&&y>=0&&(s+d)%2==0) printf("%ld %ld\n", x, y);
        else printf("impossible\n");
    }
    return 0;
}
