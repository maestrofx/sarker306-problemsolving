#include<stdio.h>
#include<math.h>

#define SIZE 100005

long prime[SIZE+5];
char sieve[SIZE+50];
long count;

int main(){
	long long i, j, k;
	long long n, phi, T_n, N; /* phi =number of numbers coprime to N<=N, T_n = number of proper divisors of N */

	prime[count++]=2;
	for(i=4;i<SIZE;i+=2) sieve[i]=1;
	for(i=3;i<SIZE;i+=2){
		if(sieve[i]==0){
			prime[count++]=i;
			for(j=i*i;j<SIZE;j+=i) sieve[j]=1;
		}
	}
	
	while(scanf("%I64d", &N)!=EOF){
		phi=n=N;
		T_n=1;
		if(n==0) break;
		for(i=0, k=sqrt(N)+1;i<count && prime[i]<=k;i++){
			j=1;
			if(n%prime[i]==0){
				phi-=phi/prime[i];
				while(n%prime[i]==0) n/=prime[i], j++;
				T_n*=j;
				k=sqrt(n);
			}
		}
		
		if(n>1){
			phi-=phi/n;
			T_n*=2;
		}
		T_n--;
		printf("%I64d\n", N-phi-T_n);
	}
	
	return 0;
}
