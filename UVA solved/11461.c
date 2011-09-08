#include<stdio.h>
#include<math.h>

int main()
{
    long a, b, i, j, count;
    while (scanf("%ld%ld", &a, &b)==2 && a &&b)
    {
        i=sqrt(a);
        j=sqrt(b);
        if (i*i==a) count=j-i+1;
        else count=j-i;
        printf("%ld\n", count);
    }
    return 0;
}
