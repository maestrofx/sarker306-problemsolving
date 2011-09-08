#include<stdio.h>
#include<math.h>
int main()
{
    long x, x1, n, a;
    while(scanf("%ld", &x)==1)
    {
        n=(int)((1+sqrt(8*x+1))/2);
        x1=n*(n-1)/2;
        if(x1==x) printf("1/%ld\n", n-1);
        else printf("%ld/%ld\n", n+1-x+x1, x-x1);
    }
    return 0;
}
