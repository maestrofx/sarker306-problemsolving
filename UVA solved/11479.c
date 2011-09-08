#include<stdio.h>

int main()
{
    long a, b, c;
    int i, t;
    scanf("%d", &t);
    for(i=0;i<t;)
    {
        scanf("%ld%ld%ld", &a, &b, &c);
        if(a+b>c && b+c>a && c+a>b)
        {
            if(a==b && b==c) printf("Case %d: Equilateral\n", ++i);
            else if(a==b||b==c||c==a) printf("Case %d: Isosceles\n", ++i);
            else printf("Case %d: Scalene\n", ++i);
        }
        else printf("Case %d: Invalid\n", ++i);
    }
    return 0;
}
