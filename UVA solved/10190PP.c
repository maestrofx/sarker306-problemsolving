#include<stdio.h>
#include<math.h>

int main()
{
    long m, n, i, j, prod;
    while(scanf("%ld%ld", &m, &n)==2)
    {
        i=log(m)/log(n);
        prod=1;
        for(j=0;j<i;j++) prod*=n;
        if(prod<m) prod*=n;
        if(prod==m&& m!=1)
        {
            printf("%ld", m);
            for (i=0;m>1;i++)
            {
                m/=n;
                printf(" %ld", m);
            }
        }
        else printf("Boring!");
        printf("\n");
    }
    return 0;
}

