#include<stdio.h>
#include<math.h>

#define SIZE1 46500
#define SIZE 5000

char sieve[SIZE1];
unsigned prime[SIZE];
long counter;

int main()
{
    long i, j;
    long n, m;
    long x;
    char flag;
    
    sieve[0]=sieve[1]=1;
    prime[counter++]=2;
    for(i=4;i<SIZE1;i+=2) sieve[i]=1;
    for(i=3; i<SIZE1; i+=2)
    {
        if(sieve[i]==0)
        {
            prime[counter++]=i;
            for(j=i*i;j<SIZE1;j+=i) sieve[j]=1;
            if(counter==SIZE) break;
        }
    }
    
    while(scanf("%ld", &n)!=EOF && n)
    {
        flag = 0;
        printf("%ld = ", n);
        
        if(n<0 && n!=-1)
        {
            printf("-1 x ");
            n*=-1;
        }
        
        m=n;
        x=sqrt(n);
        for(i=0;i<counter && prime[i]<=x;i++)
        {
            while(n%prime[i]==0)
            {
                n/=prime[i];
                if(!flag)printf("%ld", prime[i]);
                else printf(" x %ld", prime[i]);
                flag=1;
            }
            if(n==1) break;
        }
        
        if(n>1||m==n)
        if(!flag)printf("%ld", n);
        else printf(" x %ld", n);
        printf("\n");
    }
    
    return 0;
}

