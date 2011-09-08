#include<stdio.h>
#include<math.h>

#define N 60000

long array[N+1];
int main()
{
    int i, j, k, n;
    array[0]=0;
    array[1]=0;
    j=sqrt(N);
    for(i=2;i<=N;i++)
    {
        for(k=i*2;k<=N;k+=i) array[k]+=i;
    }
    printf("PERFECTION OUTPUT\n");
    while(scanf("%ld", &n)==1&& n)
    {
        printf("%5d  ", n);
        if (n==1) printf("DEFICIENT\n");
        else if(array[n]+1>n) printf("ABUNDANT\n");
        else if(array[n]+1<n) printf("DEFICIENT\n");
        else printf("PERFECT\n");
    }
    printf("END OF OUTPUT\n");
    return 0;
}
