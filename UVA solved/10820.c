#include<stdio.h>
#include<math.h>

#define SIZE 50003

long prime[SIZE+5];
char sieve[SIZE+50];
long long phi[SIZE+50];
long count;

long long phigen(long long n){
	long long m=n, k, i;
	
	for(i=0, k=sqrt(n)+1;i<count && prime[i]<=k;i++){
		if(n%prime[i]==0){
			m-=m/prime[i];
			while(n%prime[i]==0) n/=prime[i];
			k=sqrt(n);
		}
	}
	
	if(n>1) m-=m/n;
	return m;
}

long gcd(long long m, long long n){
	long long temp;
	
	while(n){
		temp=m;
		m=n;
		n=temp%n;
	}
	
	return m;
}

int main(){
	long long i, j, k;
	long long n, m;

	prime[count++]=2;
	for(i=4;i<SIZE;i+=2) sieve[i]=1;
	for(i=3;i<SIZE;i+=2){
		if(sieve[i]==0){
			prime[count++]=i;
			for(j=i*i;j<SIZE;j+=i) sieve[j]=1;
		}
	}
	
	/*for(i=1;i<SIZE;i++) phi[i]=phigen(i);*/
	for(i=1;i<SIZE;i++) phi[i]=i;	    
    for(i=2;i<SIZE;i++){
		if(sieve[i]==0){
			for(j=i;j<SIZE;j+=i){
				phi[j]-=phi[j]/i;
			}
		}
    }
    
    for(i=3;i<SIZE;i++) phi[i]+=phi[i-1];
	
	while(scanf("%I64d", &n)!=EOF && n>0){
		printf("%I64d\n", (n>1)? phi[n]*2+1: 1);
	}
	
	return 0;
}
