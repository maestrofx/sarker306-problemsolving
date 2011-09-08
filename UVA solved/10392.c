#include<stdio.h>
#include<math.h>

#define SIZE1 1000000
#define SIZE 100000

char sieve[SIZE1+5];
long long prime[SIZE+5];
long long counter;

int main(){
    long long i, j;
    long long n, m;
    long long x;
    
    sieve[0]=sieve[1]=1;
    prime[counter++]=2;
    for(i=4;i<=SIZE1;i+=2) sieve[i]=1;
    for(i=3; i<=SIZE1; i+=2){
        if(sieve[i]==0){
            prime[counter++]=i;
            for(j=i*i;j<=SIZE1;j+=i) sieve[j]=1;
            if(counter==SIZE){
				printf("ERROR\n");
				break;
			}
        }
    }
    
    while(scanf("%I64d", &n)!=EOF && n){
		if(n<0) break;
        
        m=n;
        x=sqrt(n);
        for(i=0;i<counter && prime[i]<=x;i++){
            while(n%prime[i]==0){
                n/=prime[i];
                printf("    %I64d\n", prime[i]);
            }
            if(n==1) break;
        }
        
        if(n>1||m==n) printf("    %I64d\n", n);
        printf("\n");
    }
    
    return 0;
}
