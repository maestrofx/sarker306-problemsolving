#include<stdio.h>

int main()
{
    long n;
    long long m;
    while(scanf("%ld", &n)==1)
    {
        m=n+1;
        m=m/2*3*m-9;
        printf("%I64d\n", m);
    }
    return 0;
}
