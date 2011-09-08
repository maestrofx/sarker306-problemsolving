#include<stdio.h>

#define SIZE 101

unsigned long long square[SIZE], cube[SIZE], quad[SIZE];
int main()
{
    int n, i;
    unsigned long long temp;
    for(i=1;i<=100;i++)
    {
        n=i*i;
        square[i]=n+square[i-1];
        n*=i;
        cube[i]=n+cube[i-1];
        n*=i;
        quad[i]=n+quad[i-1];
    }
    while(scanf("%d", &n)==1)
    {
        temp=n*(n+1)/2;
        printf("%I64u", square[n]);
        printf(" %I64u", cube[n]-square[n]);
        printf(" %I64u", cube[n]);
        printf(" %I64u", cube[n]*(temp-1));
        printf(" %I64u", quad[n]);
        printf(" %I64u\n", cube[n]*cube[n]-quad[n]);
    }
    return 0;
}
