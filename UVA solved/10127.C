#include<stdio.h>
int main()
{
	unsigned long count, a, n;
	while(scanf("%lu", &a)==1)
	{
		n=count=1;
		while(n%a)
		{
			n=10*n+1;
			n=n%a;
			count++;
		}
		printf("%lu\n", count);
	}
	return 0;
}