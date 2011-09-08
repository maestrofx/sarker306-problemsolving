#include<stdio.h>

int main()
{
    long n, k, res, butt, m;
    long num;
    int test;
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%ld%ld%ld", &n, &m, &k);
        n+=m;
        num=0;
        res=0;
        while(n+res>=k)
        {
            butt=n+res;
            res=butt%k;
            n=butt/k;
            num+=n;
        }
        printf("%ld\n", num);
    }
    return 0;
}
