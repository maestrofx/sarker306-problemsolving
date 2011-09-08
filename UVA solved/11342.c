#include<stdio.h>
#include<math.h>

int main()
{
    int test;
    long k, a, b, c;
    double p;
    char flag;
    scanf("%d", &test);
    for(test;test; test--)
    {
        flag=0;
        scanf("%ld", &k);
        for(a=0;a*a<=k&&!flag;a++)
        {
            for(b=a;b*b<=k&&!flag;b++)
            {
                p=sqrt(k-a*a-b*b);
                c=(int)p;
                if(a*a+b*b+c*c==k)
                {
                    flag=1;
                    printf("%lu %lu %lu\n", a, b, c);
                    break;
                }
            }
        }
        if(!flag) printf("-1\n");
    }
    return 0;
}
