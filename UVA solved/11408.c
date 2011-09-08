#include<stdio.h>
#include<math.h>
#define SIZE 10000000

typedef long long llong;
char isnp[SIZE+5];
llong sumfactor[SIZE+5];
llong numofdeprimes[SIZE+5];

int main(){
	llong i, j, a, b;
	
	for(i=2, sumfactor[0]=sumfactor[1]=1;i<=SIZE;i+=2) sumfactor[i]+=2;
	for(i=3;i<=SIZE;i+=2){
		if(sumfactor[i]==0){
			for(j=i;j<=SIZE;j+=i) sumfactor[j]+=i;
		}
	}
	
	for(i=1;i<=SIZE;i++){
		if(sumfactor[i]<=SIZE && sumfactor[sumfactor[i]]==sumfactor[i]) numofdeprimes[i]=numofdeprimes[i-1]+1;
		else numofdeprimes[i]=numofdeprimes[i-1];
	}
	
	while(scanf("%lld", &a)!=EOF && a){
		scanf("%lld", &b);
		printf("%lld\n", numofdeprimes[b]-numofdeprimes[a-1]);
	}
	
	return 0;
}
