#include<stdio.h>
#include <stdbool.h>

#define SIZE 32768

bool prime[SIZE];
    
int main()
{
	long unsigned i, n, a, sum, count=1, p;
	long x, y;
    unsigned alls[3510];
	prime[0]=prime[1]=true;
	for(i=2, a=0;i<SIZE;i++)
	{
		if(prime[i]==false)
		{
            alls[a++]=i;
			for(n=2*i;n<SIZE;n=n+i)
			{
				prime[n]=true;
			}
		}
	}
	while(scanf("%ld", &y)!=EOF && y)
	{
        i=sum=0;
        x=y;
        for(i=0;i<3510;i++)
        {
            n=alls[i];
            if(n*n>x) break;
            a=1;
            if(x%n) continue;
            do
            {
                x/=n;
                a*=n;
            }while(x%n==0);
            sum+=a;
        }
        if(x>1) sum+=x;
        if(y==sum) sum++;
        if(y==1) sum=2;
        printf("Case %lu: %lu\n", count++, sum);
    }
    return 0;
}
