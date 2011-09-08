#include<stdio.h>

int array[101]={0};

int main()
{
    int i, test, a, b;
    for(i=1;i<101;i++) array[i]=array[i-1]+2*i-1;
    scanf("%d", &test);
    for(i=0;i<test;i++)
    {
        scanf("%d%d", &a, &b);
        if(a%2==1) a=(a-1)/2;
        else a=a/2;
        if(b%2==1) b=(b+1)/2;
        else b=b/2;
        printf("Case %d: %d\n", i+1, array[b]-array[a]);
    }
    return 0;
}
