#include<stdio.h>
#include<math.h>

#define SIZE 100005

long prime[SIZE+5];
char sieve[SIZE+50];
long count;

long powerinfactorial(long n, long k){
	long sum;
	long p;
	
	for(sum=0, p=k; n>=p;p*=k){
		sum+=n/p;
	}
	
	return sum;
}

int main(){
	long n, k;
	long long i, j, p;
	
	prime[count++]=2;
	for(i=4;i<SIZE;i+=2) sieve[i]=1;
	for(i=3;i<SIZE;i+=2){
		if(sieve[i]==0){
			prime[count++]=i;
			for(j=i*i;j<SIZE;j+=i) sieve[j]=1;
		}
	}
	
	while(scanf("%ld%ld", &n, &k)!=EOF){
		printf("%ld", k);
		for(i=0, p=sqrt(k)+1;i<count && prime[i]<=p;i++){
			j=0;
			if(k%prime[i]==0){
				while(k%prime[i]==0) k/=prime[i], j++;
				p=sqrt(k);
				if(powerinfactorial(n, prime[i])<j){
					p=-1;
					break;
				}
			}
		}
		
		if(k>1){
			if(powerinfactorial(n, k)<1) p=-1;
		}
		
		printf("%s%ld!\n", (p==-1)? " does not divide ":" divides ", n);
	}
	
	return 0;
}
