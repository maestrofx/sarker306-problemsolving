#include<stdio.h>
#include<math.h>
#define SIZE 1000005

typedef long long llong;
char isnp[SIZE+5];

int main(){
	llong i, j, n=ceil(sqrt(SIZE)+0.5);
	char flag;
	
	for(i=4;i<=SIZE;i+=2) isnp[i]=1;
	for(i=3;i<=SIZE;i+=2){
		if(isnp[i]==0){
			for(j=i*i;j<=SIZE;j+=i) isnp[j]=1;
		}
	}
	
	while(scanf("%lld", &n)!=EOF && n>0 && n<SIZE){
		flag=0;
		printf("%lld:\n", n);
		if(!isnp[n-2]) printf("2+%lld\n", n-2), flag=1;
		else for(i=3;2*i<=n;i+=2) if(!isnp[i] && !isnp[n-i]){
			printf("%lld+%lld\n", i, n-i);
			flag=1;
			break;
		}
		if(!flag) printf("NO WAY!\n");
	}
	
	return 0;
}
