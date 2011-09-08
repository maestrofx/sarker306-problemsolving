#include<stdio.h>
#include<math.h>
#define SIZE 500001

typedef long long llong;
llong sumoffactor[SIZE+5];
llong cycle[SIZE+5];

int main(){
	llong i, j, n=ceil(sqrt(SIZE)), test;
	llong a, b, max;

	for(i=4;i<=SIZE;i+=2) sumoffactor[i]=2;
	for(i=3;i<=n;i+=2){
		if(sumoffactor[i]==0){
			for(j=i*i;j<=SIZE;j+=i) sumoffactor[j]=i;
		}
	}

	for(i=2;i<=SIZE;i++){
		n=(sumoffactor[i])? sumoffactor[i]:i;
		sumoffactor[i]=n+sumoffactor[i/n];
		cycle[i]=1+cycle[sumoffactor[i]];
	}
	
	while(scanf("%lld", &test)!=EOF){
		for(i=1;i<=test;i++){
			scanf("%lld%lld", &a, &b);
			if(a>b) a^=b^=a^=b; 
			for(max=-9999; a<=b;a++) if(max<cycle[a]) max=cycle[a];
			printf("Case #%lld:\n%lld\n", i, max);
		}
	}

	return 0;
}
