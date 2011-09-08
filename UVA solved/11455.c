#include<stdio.h>

int main()
{
    long unsigned a, b, c, d, test;
    scanf("%lu", &test);
    for(;test;test--)
    {
        scanf("%lu%lu%lu%lu", &a, &b, &c, &d);
        if(a==b && b==c && c==d) printf("square\n");
        else if(a==b && c==d||a==c && b==d||a==d && b==c) printf("rectangle\n");
        else if(a+b+c>d && a+c+d>b && b+c+d>a && a+b+d>c) printf("quadrangle\n");
        else printf("banana\n");
    }
    return 0;
}
