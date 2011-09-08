#include<stdio.h>
#include<math.h>

int main(){
    long long n, k, i;
    double logs;
    
    while(scanf("%lld%lld", &n, &k)!=EOF){
        if(2*k>n) k=n-k;
        for(i=1, logs=0;i<=k;i++) logs+=log10(n-i+1)-log10(i);
        
        printf("%ld\n", (long)logs+1);
    }
    
    return 0;
}
