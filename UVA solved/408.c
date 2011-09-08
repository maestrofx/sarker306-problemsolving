#include<stdio.h>

int main()
{
    long step, mod, temp, m, n;
    while(scanf("%ld%ld", &step, &mod)==2)
    {
        m=step, n=mod;
        if(m<n)
        {
            temp=m;
            m=n;
            n=temp;
        }
        while(n)
        {
            temp=m%n;
            m=n;
            n=temp;
        }
        printf("%10ld%10ld    ", step, mod);
        if(m==1) printf("Good Choice\n\n");
        else printf("Bad Choice\n\n");
    }
    return 0;
}
