#include<stdio.h>
#include<math.h>

#define SIZE 10000002

long long isnp[SIZE+5];
long long prime[SIZE];
long count;

void init(){
	long long i, j, k=sqrt(SIZE);

	prime[count++]=2;
	for(i=3;i<=SIZE;i+=2){
		if(isnp[i]==0){
			prime[count++]=i;
			for(j=i*i;j<SIZE;j+=i) isnp[j]=i;
		}
	}
}

int main(){
	long long n, k, i, max, m, temp;
	int flag;

	init();
	while(scanf("%I64d", &n)==1){
		if(n==0) break;
		if(n<0) n*=-1;

		max=-1, temp=n;
		for(i=0, flag=0;i<count && prime[i]*prime[i]<=n;i++){
			m=n;
			while(n%prime[i]==0) n/=prime[i];
			if(m!=n){
				max=prime[i];
				flag++;
			}
		}

		if(n>1) max=n, flag++;
		if(n==temp) max=-1;
		else if(flag==1) max=-1;
		printf("%I64d", max);

		printf("\n");

	}

	return 0;
}
