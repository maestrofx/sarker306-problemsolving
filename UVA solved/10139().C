#include<stdio.h>
#include<math.h>
unsigned long count;
long unsigned numberoffactor(long unsigned x)
{
	long unsigned product=1, i, count=0,j=sqrt(x), temp;
	while(x%2==0)
	{
		temp=2;
		x=x/2;
		count++;
	}
	for(i=3;i<=j;i=i+2)
	{
		for(count=0;x%i==0;count++)
		{
			x/=i;
			temp=i;
		}
	}
	if(x!=1)temp=x;
	return temp;
}
int main()
{
	unsigned long n,m,temp;
	while(scanf("%lu %lu", &n, &m)==2)
	{
		if (n%(temp=numberoffactor(m)))
			printf("%lu does not divide %lu!\n",m,n);
		else if(n%(long unsigned)pow(temp,count))
			printf("%lu does not divide %lu!\n",m,n);
			else printf("%lu divides %lu!\n", m,n);
	}
	return 0;
}