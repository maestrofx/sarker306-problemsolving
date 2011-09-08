#include<stdio.h>
#include<math.h>

long fastexp(long b,long p){
	long int c;
	if(p==0) return 1;
	else if(p%2==0){
		c=fastexp(b,p/2);
		return c*c;
	}
	else return b*fastexp(b,p-1);
}

int main(){
    long N, M, level, ans, temp;
    
    while(scanf("%ld%ld", &N, &M)!=EOF && N && M){
        printf("%ld %ld ", N, M);
        if(N==1){
            if(M==1) printf("Multiple\n");
            else printf("Impossible\n");
        }
        else{
            level=log(M)/log(N);
            if((temp=fastexp(N, level))==M){
                ans=( temp*N-1) / (N-1);
                printf("%ld\n", ans);
            }
            else{
                if( (M-temp)%(N-1)==0 ){
                    ans=( temp*N-1) / (N-1)+M-temp;
                    printf("%ld\n", ans+(M-temp)/(N-1));
                }
                else printf("Impossible\n");
            }
        }
    }
    
    return 0;
}
