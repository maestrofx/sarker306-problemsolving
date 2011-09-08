#include<stdio.h>

int main()
{
    int test;
    long n;
    scanf("%d", &test);
    for(;test;test--)
    {
        scanf("%ld", &n);
        n=(315*n+36962)%100;
        n/=10;
        if(n<0) n*=-1;
        printf("%d\n", n);
    }
    return 0;
}
