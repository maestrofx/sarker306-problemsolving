#include<stdio.h>

long int bigmod(long int b,long int p,long int m){
	long int c;
	
	if(p==0) return 1;
	else if(p%2==0){
		c=bigmod(b,p/2,m);
		return (c*c)%m;
	}
	else return ((b%m)*bigmod(b,p-1,m))%m;
}

int main(){
    long N, M, K, i, ans, test, j, x, sum;
    
    while(scanf("%ld", &test)!=EOF){
        for(j=1;j<=test;j++){
            scanf("%ld%ld%ld", &N, &K, &M);
            ans=((K%M)*bigmod(N, K-1, M))%M;
            for(sum=0;N;N--){
                scanf("%ld", &x);
                sum=(sum+x)%M;
            }
            
            printf("Case %ld: %ld\n", j, (ans*sum)%M);
        }
    }
    
    return 0;
}
