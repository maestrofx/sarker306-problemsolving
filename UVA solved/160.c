#include<stdio.h>
#include<stdbool.h>

#define SIZE 101

int main()
{
  	bool prime[SIZE];
	unsigned i,n, x, count, p, fucker;
	prime[0]=prime[1]=false;
	for(i=2;i<SIZE;i++)
		prime[i]=true;
	for(i=2;i<SIZE;i++)
	{
		if(prime[i]==true)
		{
			for(n=2*i;n<SIZE;n=n+i)
			{
				prime[n]=false;
			}
		}
	}
	while(scanf("%d",&n)==1 && n>0 && n<101)
	{
        printf("%3d! =", n);
        fucker=0;
        for(i=0;i<=n;i++)
        {
            if(prime[i])
            {
                count=0;
                x=i;
                do
                {
                    p=n/x;
                    count+=p;
                    x*=i;
                }while(p);
                if(fucker==15) printf("\n      ");
                printf("%3d", count);
                fucker++;
            }
        }
        printf("\n");
    }
    return 0;
}
