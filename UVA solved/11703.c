#include<stdio.h>
#include<math.h>

unsigned long array[1000002];
int main()
{
    long unsigned a, b, c, i;
    long n;
    double d, x, p;
    array[0]=1;
    for(i=1; i<=1000000; i++)
    {
        x=i;
        x-=sqrt(i);
        a=x;
        b=log(i);
        p=sin(i);
        d=p*p*i;
        c=d;
        array[i]=(array[a]+array[b]+array[c])%1000000;
    }
    while(scanf("%ld", &n)==1 && n>=0) printf("%lu\n", array[n]);
    return 0;
}
