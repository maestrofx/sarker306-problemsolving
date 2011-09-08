#include<stdio.h>
#include<math.h>

int main()
{
    double x;
    long n;
    register int l;
    while(scanf("%ld",&n)!=EOF && n!=0)
    {
        for(l=0; ;l++)
        {
            x=1-n/exp(l);
            if(x+1>0.000000001 && x-1<0.000000001)
            break;
        }
        printf("%d %.8lf\n", l,x);
    }
    return 0;
}
