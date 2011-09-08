#include<stdio.h>

int main()
{
    unsigned long num=0;
    while(scanf("%lu", &num)==1&&num)
    {
        printf("%d\n", num%9+9*(num%9==0));
    }
    return 0;
}
