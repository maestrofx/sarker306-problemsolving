#include<stdio.h>

int main()
{
    unsigned long n, k, res, butt, m;
    unsigned long long num;
    while(scanf("%lu%lu", &n, &k)==2)
    {
        num=0;
        res=0;
        num=n;
        while(n+res>=k)
        {
            butt=n+res;
            res=butt%k;
            n=butt/k;
            num+=n;
        }
        printf("%I64u\n", num);
    }
    return 0;
}
