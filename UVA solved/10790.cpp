#include<stdio.h>

#define C(x) (x%2)? (x-1)/2*x: x/2*(x-1)

int main()
{
    long m, n, i=1;
    unsigned long long ans;
    while(scanf("%ld%ld", &m, &n)!=EOF && m||n)
    {
        ans=C(m);
        ans*=C(n);
        printf("Case %d: %llu\n", i++, ans);
    }
    return 0;
}
