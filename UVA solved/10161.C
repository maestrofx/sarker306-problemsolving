#include<stdio.h>
#include<math.h>
int main()
{
	unsigned long N, R, C, n, k;
	double m;
	scanf("%lu", &N);
	while(N)
    {
		m=sqrt(N);
		if(m!=(int)m)
		{
			n=(int)m+1;
			k=n*n-n+1;
			if((k>N)&&(n%2))
			{
				C=n;
				R=N-(n-1)*(n-1);
			}
			else if((k>N)&&!(n%2))
			{
				R=n;
				C=N-(n-1)*(n-1);
			}
			else if((k<N)&&(n%2))
			{
				R=n;
				C=n*n-N+1;
			}
			else
			{
				C=n;
				R=n*n-N+1;
			}
		}
		else
		{
			n=(int)m;
			if(n%2)
			{
				C=1;
				R=n;
			}
			else
			{
				R=1;
				C=n;
			}
		}
		printf("%lu %lu\n", C, R);
		scanf("%lu", &N);
	}
	return 0;
}