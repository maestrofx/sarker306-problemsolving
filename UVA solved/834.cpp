#include<iostream>
using namespace std;
int main()
{
	long a, b, c;
	while(scanf("%ld %ld", &a, &b)&&(b))
	{
		printf("[%ld;",a/b);
		c=a%b;
		a=b;
		b=c;
		printf("%ld",a/b);
		while((b>1)&&(a%b))
		{
			c=a%b;
			a=b;
			b=c;
			printf(",%ld",a/b);
		}
		printf("]\n");
		a=b=0;
	}
	return 0;
}