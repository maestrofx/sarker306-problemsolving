#include<stdio.h>
#include<math.h>
long unsigned numberoffactor(long unsigned x)
{
	long unsigned product=1, i, count=0,j=sqrt(x);
	while(x%2==0)
	{
		x=x/2;
		count++;
	}
	product=product*(1+count);
	for(i=3;i<=j;i=i+2)
	{
		for(count=0;x%i==0;count++)
		x/=i;
		product=product*(1+count);
	}
	if(x!=1) product*=2;
	return product;
}
int main()
{
	long unsigned maxfactor, maxfactorednum, number, low, high, temp, range,I;
	scanf("%lu", &range);
	for(I=range;I;I--)
	{
		scanf("%lu", &low);
		scanf("%lu", &high);
		maxfactor=0;
		maxfactorednum=low;
		for(number=low;number<=high;number++)
		{
			temp=numberoffactor(number);
			if(maxfactor<temp)
			{
				maxfactorednum=number;
				maxfactor=temp;
			}
		}
		printf("Between %lu and %lu, %lu has a maximum of %lu divisors.\n", low, high, maxfactorednum, maxfactor);
	}
	return 0;
}