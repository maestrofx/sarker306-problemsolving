#include<stdio.h>

int main()
{
    long n, i, a, b, j, x;
    int p;
    while(scanf("%ld", &p)==1)
    {
        if(p==2) n=100, p=10, x=1;
        else if(p==4) n=10000, p=100, x=2;
        else if(p==6) n=1000000, p=1000, x=3;
        else n=100000000, p=10000, x=4;
        for(i=0;i*i<n;i++)
        {
            j=i*i;
            a=j/p, b=j%p;
            if((a+b)*(a+b)==j) printf("%0*d%0*d\n", x, a, x, b);
        }
    }
    return 0;
}
