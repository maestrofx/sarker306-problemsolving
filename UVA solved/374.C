#include<stdio.h>
long int bigmod(long int b,long int p,long int m)
{
	long int c;
	if(p==0) return 1;
	else if(p%2==0)
	{
		c=bigmod(b,p/2,m);
		return (c*c)%m;
	}
	else return ((b%m)*bigmod(b,p-1,m))%m;
}
int main()
{
	long int B,P,M;
	while(scanf("%ld %ld %ld", &B, &P, &M)==3)
	{
		printf("%ld\n",bigmod(B,P,M));
	}
	return 0;
}