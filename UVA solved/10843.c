#include<stdio.h>

unsigned long long bigmod(unsigned long b,unsigned long p);

int main()
{
    unsigned long n, test, i;
    unsigned long long array[101];
    array[0]=0;
    array[1]=1;
    for(i=2;i<=100;i++) array[i]=bigmod(i, i-2);
    scanf("%lu", &test);
    for(i=0;i<test;)
    {
        scanf("%lu", &n);
        printf("Case #%u: %I64u\n", ++i, array[n]);
    }
    return 0;
}

unsigned long long bigmod(unsigned long b,unsigned long p)
{
	unsigned long long c;
	unsigned long m=2000000011;
	if(p==0) return 1;
	else if(p%2==0)
	{
		c=bigmod(b,p/2);
		return (c*c)%m;
	}
	else return ((b%m)*bigmod(b,p-1))%m;
}
