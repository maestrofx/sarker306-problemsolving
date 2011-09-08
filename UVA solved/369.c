#include<stdio.h>

int main()
{
    unsigned long n, k, p, i;
    double nCk;
    while(scanf("%lu%lu", &n, &k)==2 && (n)||(k))
    {
        p=k;
        if(p*2>n) p=n-p;
        if(p==0) nCk=1;
        else nCk=n;
        for(i=2;i<=p;i++)
        nCk=nCk/i*(n-i+1);
        printf("%lu things taken %lu at a time is %.0lf exactly.\n", n, k, nCk);
    }
    return 0;
}
