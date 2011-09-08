#include<stdio.h>

int main()
{
    long long n, k;
    int test;
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%I64d%I64d", &n, &k);
        if(n%k) printf("%I64d %I64d\n", -n, n);
        else printf("0 %I64d\n", k);
    }
    return 0;
}
