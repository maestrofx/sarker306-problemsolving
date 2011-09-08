#include<stdio.h>

#define SIZE 501

int main()
{
    long array[SIZE]={0};
    long G, m, n, temp, N, i, j;
    while(scanf("%ld", &N)==1 && N)
    { 
        G=0;
        for(i=1;i<N;i++)
        {
            for(j=i+1;j<=N;j++)
            {
                m=i, n=j;
                while(n)
                {
                    temp=n;
                    n=m%n;
                    m=temp;
                }
                G+=m;
            }
        }
        printf("%ld\n", G);
    }
    return 0;
}
