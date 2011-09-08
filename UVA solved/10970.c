#include<stdio.h>

int main()
{
    unsigned long m, n;
    while(scanf("%lu%lu", &m, &n)==2) printf("%lu\n", m*n-1);
    return 0;
}
