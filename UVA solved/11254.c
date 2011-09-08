#include<stdio.h>
#include<math.h>

int main(){
    long long n, test;
    long long a, x, tmp, nn;
    
    while(scanf("%lld", &x)!=EOF){
        if(x==-1) break;
        for(n=1;n*(n+1)<=2*x;n++){
            if((2*x)%n==0){
                tmp=(2*x)/n+1-n;
                if(tmp%2==0) a=tmp/2, nn=n;
            }
        }
        
        printf("%lld = %lld + ... + %lld\n", x, a, a+nn-1);
    }
    
    return 0;
}
