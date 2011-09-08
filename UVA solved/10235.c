#include<stdio.h>
#include<stdbool.h>

#define SIZE 1000002

int main()
{
    bool PRIME[SIZE];
	long i,n,a,b;
	PRIME[0]=false;
	PRIME[1]=true;
	for(i=2;i<SIZE;i++)
		PRIME[i]=true;
	for(i=2;i<SIZE;i++)
	{
		if(PRIME[i]==true)
		{
			for(n=2*i;n<SIZE;n=n+i)
			{
				PRIME[n]=false;
			}
		}
	}
	while(scanf("%ld", &n)==1 && n)
	{
        for(a=0, b=n;b;b/=10) a=10*a+b%10;
        if(PRIME[n])
        {
            if(n!=a && PRIME[a]) printf("%ld is emirp.", n);
            else printf("%ld is prime.", n);
        }
        else printf("%ld is not prime.", n);
        printf("\n");
    }
    return 0;
}
