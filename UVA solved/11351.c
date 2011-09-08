#include<stdio.h>

long josephus(long n, long x);

int main()
{
  long n, x, k, cases;
  scanf("%ld", &cases);
  for(k=0;k<cases;k++)
  {
	scanf("%ld%ld", &n, &x);
    printf("Case %d: %lu\n", k+1, josephus(n, x)+1);
  }
  return 0;
}

long josephus(long n, long x)
{
    if(n==1) return 0;
    else return (josephus( n-1, x)+x)%n;
}
