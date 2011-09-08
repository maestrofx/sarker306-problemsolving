/*
  Name: 264
  Copyright: 
  Author: 
  Date: 09/09/09 22:37
  Description: Count On Cantor
*/
#include<stdio.h>
#include<math.h>
int main()
{
    long x, x1, n, a;
    while(scanf("%ld", &x)==1)
    {
        n=(1+sqrt(8*x+1))/2;
        x1=n*(n+1)/2;
        printf("TERM %ld IS ", x);
        if (x1==x+n)
        {
            x1=x;
            n--;
        }
        if(n%2==1)
        {
            a=x1-x;
            printf("%ld/%ld\n", a+1, n-a);
        }
        else
        {
            a=x-x1+n+1;
            printf("%ld/%ld\n", a-1, n-a+2);
        }
    }
    return 0;
}
