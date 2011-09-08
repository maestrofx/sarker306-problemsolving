#include<stdio.h>
#include<math.h>
#define SIZE 2703664

typedef long long llong;
llong countfact[SIZE+5];
llong answer[10000005];

int main(){
	llong i, j, n=ceil(sqrt(SIZE)), test;
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
    while(scanf("%lld", &test)!=EOF){
        while(test--){
            scanf("%lld", &n);
            if(answer[n]) mid=answer[n];
            else{
                low=0, high=SIZE+1;
                while(low+1<high){
                    mid=(low+high)/2;
                    if(countfact[mid]>n) high=mid;
                    else low=mid;
                }
                if(countfact[mid+1]>n && countfact[mid]<=n) mid++;
                answer[n]=mid;
            }
            printf("%lld\n", mid);
        }
    }

	return 0;
}
