#include<stdio.h>
#include<stdbool.h>

#define SIZE 10000006

bool prime[SIZE];
long all_p[100002];

int main()
{
    long i, j, k;
    for(i=0, k=0;i<SIZE;i++)
    {
        if(prime[i]==false)
        {
            for(j=3*i+3; j<SIZE; j+=2*i+3) prime[j]=true;
            if(i+1<SIZE && prime[i+1]==false) all_p[k++]=2*i+3;
        }
    }
    while(scanf("%ld", &i)!=EOF && i<k && i>=0) printf("(%ld, %ld)\n", all_p[i-1], 2+all_p[i-1]);
    return 0;
}
