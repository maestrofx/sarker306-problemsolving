#include<stdio.h>
#include<math.h>

int main()
{
    long test, x, y, n, m;
    scanf("%ld", &test);
    for(;test;test--)
    {
        scanf("%ld%ld", &x, &y);
        n=y-x;
        if(n)
        {
            m=sqrt(n);
            if(m*m==n) printf("%ld\n", 2*m-1);
            else if(m*(m+1)>=n) printf("%ld\n", 2*m);
            else printf("%ld\n", 2*m+1);
        }
        else printf("0\n");
    }
    return 0;
}
