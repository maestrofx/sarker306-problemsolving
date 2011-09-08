#include<stdio.h>
#include<stdbool.h>

#define SIZE 10000

int main()
{
    bool PRIME[SIZE];
    long all_prime[1232];
	long i,j,n,a, count;
	PRIME[0]=PRIME[1]=false;
	for(i=2;i<SIZE;i++)
		PRIME[i]=true;
	for(i=2;i<SIZE;i++)
	{
		if(PRIME[i]==true)
		{
            all_prime[j++]=i;
			for(n=2*i;n<SIZE;n=n+i)
			{
				PRIME[n]=false;
			}
		}
	}
	while(scanf("%ld",&n)==1 && n)
	{
        a=n;
        for(j=0, count=0;;j++)
        {
            i=all_prime[j];
            if(i*i>a) break;
            if(a%i) continue;
            count++;
            while(a%i==0) a/=i;
        }
        if(a>1) count++;
        printf("%ld : %ld\n", n, count);
    }
}
/*#include<stdio.h>

int main()
{
	long j,n,a, count;
	while(scanf("%ld",&n)==1 && n)
	{
        a=n;
        for(j=2,count=0;j<10000;j++)
        {
            if(j*j>a) break;
            if(a%j) continue;
            count++;
            while(a%j==0) a/=j;
        }
        if(a>1) count++;
        printf("%ld : %ld\n", n, count);
    }
}
*/
