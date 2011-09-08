#include<stdio.h>
#include<math.h>

int array[51];

int main()
{
    int x, pair;
    int i, j, temp, m, n;
    double pi;
    while(scanf("%d", &x)==1&& x)
    {
        pair=0;
        for(i=0;i<x;i++) scanf("%d", &array[i]);
        for(i=0;i+1<x;i++)
        {
            for(j=i+1;j<x;j++)
            {
                m=array[i];
                n=array[j];
                if(m<n)
                {
                    temp=m;
		            m=n;
		            n=temp;
	             }
	             while(n)
	             {
            		temp=m;
            		m=n;
            		n=temp%n;
	             }
	             if(m==1) pair++;
             }
        }
        if(!pair) printf("No estimate for this data set.\n");
        else
        {
              pi=2*pair;
              pi/=x;
              pi/=x-1;
              pi=6/pi;
              pi=sqrt(pi);
              printf("%lf\n", pi);
        }
    }
    return 0;
}
