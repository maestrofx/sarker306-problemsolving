#include<stdio.h>

int main()
{
    unsigned long n, k, i;
    double nCk;
    while(scanf("%lu%lu", &n, &k)==2 && (n)||(k))
    {
        if(k*2>n) k=n-k;
        if(k==0) nCk=1;
        else nCk=n;
        for(i=2;i<=k;i++)
        nCk=nCk/i*(n-i+1);
        printf("%.0lf\n", nCk);
    }
    return 0;
}
