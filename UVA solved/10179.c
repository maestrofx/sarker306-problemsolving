#include<stdio.h>
#include<math.h>

#define SIZE 100005

long prime[SIZE+5];
char sieve[SIZE+50];
long count;

int main(){
	long long i, j;
	long long n, m;

	prime[count++]=2;
	for(i=4;i<SIZE;i+=2) sieve[i]=1;
	for(i=3;i<SIZE;i+=2){
		if(sieve[i]==0){
			prime[count++]=i;
			for(j=i*i;j<SIZE;j+=i) sieve[j]=1;
		}
	}
	
	while(scanf("%I64d", &n)!=EOF){
		m=n;
		if(n==0) break;
		for(i=0;i<count;i++){
			if(n%prime[i]==0){
				m-=m/prime[i];
				while(n%prime[i]==0) n/=prime[i];
			}
		}
		
		if(n>1) m-=m/n;
		printf("%I64d\n", m);
	}
	
	return 0;
}
