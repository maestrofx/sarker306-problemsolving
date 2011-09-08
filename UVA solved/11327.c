#include<stdio.h>
#include<math.h>

#define SIZE 200005

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
	long low, high, mid;

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
    for(i=1, phi[1]=2;i<SIZE;i++) phi[i]+=phi[i-1];
	
	while(scanf("%I64d", &n)!=EOF){
		if(n==0) break;
		low=0, high=SIZE;
		while(low+1<high){
			mid=(low+high)/2;
			if(phi[mid]>n) high=mid;
			else low=mid;
			if(phi[mid]==n || (phi[mid-1]<n && phi[mid]>n)) break;
		}
		
		/*printf("%5ld -> %10I64d\n", mid, phi[mid]);*/
		if(n==1) i=0;
		else{
			n-=phi[mid-1];
			if(n==1) i=1;
			else for(i=2, --n;i<mid;){
				if(gcd(mid,i)==1) n--;
				if(n==0) break;
				i++;
			}
		}
		if(mid==1 && i==2) i=1;
		printf("%I64d/%ld\n", i, mid);
	}
	
	return 0;
}
