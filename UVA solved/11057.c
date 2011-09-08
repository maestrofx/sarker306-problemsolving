#include<stdio.h>
#include<stdlib.h>

int main()
{
    long n,i,j,taka,sum,dam[10009],ni,nj,dif,dif1;
    while(scanf("%ld",&n)==1)
    {
        dif1= 1000001;
        ni=nj=-1;
        for(i=0;i<n;i++)
        scanf("%ld",&dam[i]);
        scanf("%ld",&taka);
        for(i=0;i<n-1;i++)
        {
            for(j=i;j<n;j++)
            {
                if(dam[i]+dam[j]==taka)
                {
                    dif=abs(dam[i]-dam[j]);
                    if(dif<dif1)
                    {
                        dif1=dif;
                        ni=i;
                        nj=j;
                    }
                    
                }
            }
        }
        if(dam[ni]>dam[nj])
        printf("Peter should buy books whose prices are %ld and %ld.\n",dam[nj],dam[ni]);
        else
        printf("Peter should buy books whose prices are %ld and %ld.\n",dam[ni],dam[nj]);
        printf("\n");
    }
    return 0;
}
