#include<stdio.h>
int main()
{
	long unsigned n;
	int i, j, tag, k, test,array[50];
	scanf("%lu", &test);
	for(k=0;k<test;k++)
	{
		scanf("%lu", &n);
		if(n>1)
		{
		j=0;
		for(i=9;i>1;i--)
		{
			while(n%i==0)
			{
				array[j]=i;
				j++;
				n=n/i;
			}
		}
		if(n==1)
		for(tag=j-1;tag>=0;tag--)
			printf("%d", array[tag]);
		else printf("-1");
		}
		else printf("%lu", n);
		printf("\n");
	}
	return 0;
}