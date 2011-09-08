#include<stdio.h>
#include<math.h>
#define SIZE 2703664

typedef long long llong;
llong countfact[SIZE+5];
llong answer[10000005];

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
        if(answer[n]) mid=answer[n];
        else{
            low=0, high=SIZE+1;
            while(low+1<high){
                mid=(low+high)/2;
                if(countfact[mid]>n) high=mid;
                else low=mid;
            }
            
            if(countfact[mid-1]==n) mid--;
            if(countfact[mid]!=n) mid=-1;
            answer[n]=mid;
        }
        
        if(mid!=-1) printf("Case %lld: %lld!\n", ++test, mid);
        else printf("Case %lld: Not possible.\n", ++test);
    }

	return 0;
}
