#include<stdio.h>

int main()
{
    int test;
    int ampl, freq;
    int i, j, k, l;
    
    scanf("%d", &test);
    for(i=0;i<test;i++)
    {
        scanf("%d%d", &ampl, &freq);
        if(i) printf("\n");
        for(j=0;j<freq;j++)
        {
            if(j) printf("\n");
            for(k=0;k<ampl;k++)
            {
                for(l=0;l<=k;l++)
                printf("%d", k+1);
                printf("\n");
            }
            for(k-=1;k;k--)
            {
                for(l=0;l<k;l++)
                printf("%d", k);
                printf("\n");
            }
        }
    }
    return 0;
}
