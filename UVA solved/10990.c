#include<stdio.h>
#include<math.h>

#define SIZE 2000005

char sieve[SIZE];
long long phi[SIZE];
long depthphi[SIZE];

int main(){
	long long i, j;
	int test;
	long start, end;
	
	for(i=4;i<SIZE;i+=2) sieve[i]=1;
	for(i=3;i<SIZE;i+=2){
		if(sieve[i]==0){
			for(j=i*i;j<SIZE;j+=i) sieve[j]=1;
		}
	}
	
	for(i=1;i<SIZE;i++) phi[i]=i;	    
    for(i=2;i<SIZE;i++){
		if(sieve[i]==0){
			for(j=i;j<SIZE;j+=i){
				phi[j]-=phi[j]/i;
			}
		}
    }
    
    for(i=2;i<SIZE;i++) depthphi[i]=depthphi[phi[i]]+1;
    for(i=2;i<SIZE;i++) depthphi[i]+=depthphi[i-1];
    
    scanf("%d", &test);
    while(test--){
		scanf("%ld%ld", &start, &end);
		printf("%ld\n", depthphi[end]-depthphi[start-1]);
    }
    
    return 0;
}
