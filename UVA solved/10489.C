#include<stdio.h>
int main()
{
	long int T, B, N, i, j, k, l, a, prod, sum;
	scanf("%ld", &T);
	for(i=0; i<T;i++)
	{
		scanf("%ld %ld", &N, &B);
		sum=0;
		for(j=0;j<B;j++)
		{
			scanf("%ld", &k);
			prod=1;
			for(l=0;l<k;l++)
			{
				scanf("%ld", &a);
				prod=(prod%N)*(a%N);
			}
			sum=sum+prod;
		}
		printf("%ld\n", sum%N);
	}
	return 0;
}