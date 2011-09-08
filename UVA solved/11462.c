#include<stdio.h>

int main()
{
    long year[101];
    long n, x;
    char flag;
    int i;
    while(scanf("%ld",&n)==1 && n>0)
    {
        flag=0;
        for(i=0;i<101;i++) year[i]=0;
        for(;n;n--)
        {
            scanf("%d", &i);
            year[i]++;
        }
        for(i=0;i<101;i++)
        {
            x=year[i];
            if(x) for(;x;x--)
            {
                if(flag) printf(" ");
                printf("%d", i);
                flag=1;
            }
        }
        printf("\n");
    }
    return 0;
}
