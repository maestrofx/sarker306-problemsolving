#include<stdio.h>

typedef long long llong;

llong sum(llong n){
    return (n*(n+1))>>1;
}

llong udvotsum(llong n){
    llong x=0, y=n/10;
    
    if(n<10) return sum(n);
    else return y*45+sum(n%10)+udvotsum(y);
}

int main(){
    llong p, q;
    
    while(scanf("%lld%lld", &p, &q)==2){
        if(p<0 || q<0) break;
        printf("%lld\n", udvotsum(q)-udvotsum(p-1));
    }
    
    return 0;
}
