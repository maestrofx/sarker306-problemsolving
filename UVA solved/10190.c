#include<stdio.h>

int main()
{
    long m, n, i, j, prod;
    char flag;
    while(scanf("%ld%ld", &m, &n)==2)
    {
        flag=1;
        i=m;
        if(i==1) flag=0;
        while(i>1)
        {
            if(i%n)
            {
                flag=0;
                break;
            }
            else i/=n;
        }
        if(flag==0)printf("Boring!");
        else 
        {
            printf("%ld", m);
            while(m>1)
            {
                m/=n;
                printf(" %ld", m);
            }
        }
        printf("\n");
    }
    return 0;
}
