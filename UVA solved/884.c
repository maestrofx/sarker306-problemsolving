#include<stdio.h>
#include<math.h>
#define SIZE 1000000

typedef long long llong;
llong countfact[SIZE+5];

int main(){
	llong i, j, n=ceil(sqrt(SIZE)), test=0;
	llong low, high, mid;

	for(i=4;i<=SIZE;i+=2) countfact[i]=2;
	for(i=3;i<=n;i+=2){
		if(countfact[i]==0){
			for(j=i*i;j<=SIZE;j+=i) countfact[j]=i;
		}
	}

	for(i=2;i<=SIZE;i++){
		n=(countfact[i])? countfact[i]:i;
		countfact[i]=1+countfact[i/n];
	}

	for(i=2;i<=SIZE;i++) countfact[i]+=countfact[i-1];
	
    while(scanf("%lld", &n)!=EOF && n>=0){
        printf("%lld\n", countfact[n]);
    }

	return 0;
}
