#include<stdio.h>
int main()
{
    int test;
    int i;
    long a, b;
    scanf("%d", &test);
    for(i=0;i<test;i++)
    {
        scanf("%ld%ld", &a, &b);
        if(a==b) printf("=\n");
        else if (a<b) printf("<\n");
        else printf(">\n");
    }
    return 0;
}
