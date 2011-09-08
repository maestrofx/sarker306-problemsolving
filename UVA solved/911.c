#include<stdio.h>

typedef long long llong;

llong nCr(llong n, llong k){
	llong i, product=1;
	if(k*2>n) k=n-k;
	for(i=1;i<=k;i++){
		if(product%i==0){
			product/=i;
			product*=n-i+1;
		}
		else{
			product*=(n-i+1)/i;
		}
	}
	
	return product;
}

int main(){
	llong n, k, coeff;
	llong i, j;
	
	while(scanf("%lld%lld", &n, &k)!=EOF){
		coeff=1;
		while(k--){
			scanf("%lld", &j);
			coeff*=nCr(n, j);
			n-=j;
		}
		printf("%lld\n", coeff);
	}
	
	return 0;
}
