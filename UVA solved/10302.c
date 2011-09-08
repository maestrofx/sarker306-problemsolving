#include<stdio.h>

int main()
{
    unsigned a;
    unsigned long long b;
    while(scanf("%u", &a)==1)
    {
        b=a*(a+1)/2;
        b*=b;
        printf("%I64u\n", b);  /*submit to UVa using llu instead of I64u*/
    }
    return 0;
}
