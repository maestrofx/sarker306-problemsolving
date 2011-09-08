#include<stdio.h>
#include<stdbool.h>

#define SIZE 1000002

int main()
{
    bool PRIME[SIZE];
	long i,n,a,b;
	PRIME[0]=PRIME[1]=false;
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
        for(i=3;;i+=2) if(PRIME[i] && PRIME[n-i]) break;
        printf("%ld = %ld + %ld\n", n, i, n-i);
    }
    return 0;
}
