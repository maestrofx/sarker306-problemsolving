#include<stdio.h>

int main()
{
    int n, i, m, prod, count=0;
    while(scanf("%d", &n)==1 && n>0)
    {
        prod=1;
        m=n;
        for(i=0;n>=2;i++)
        {
            n>>=1;
            prod<<=1;
        }
        if(m==prod) printf("Case %d: %d\n", ++count, i);
        else printf("Case %d: %d\n", ++count, i+1);
    }
    return 0;
}
