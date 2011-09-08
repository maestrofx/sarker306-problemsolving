#include<stdio.h>

int main()
{
    int n;
    long test=0;
    for(;;)
    {
        scanf("%d", &n);
        if(n==0) break;
        printf("Case %ld: %d\n", ++test, n/2);
    }
    return 0;
}
