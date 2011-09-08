#include<stdio.h>
#include<math.h>

long long zeroes(long long n){
    long long poww=10, quo=1, res, sum=0;
    
    if(n<0) return -1;
    while(poww<=n){
        res=(n/poww)*quo;
        sum+=res;
        if((n/quo)%10==0) sum-=quo-(n%poww)-1;
        poww*=10, quo*=10;
    }
    
    return sum;
}

int main(){
    long long x, m, n, b, c;
    
    while(scanf("%lld%lld", &m, &n)!=EOF && m>=0 && n>=0){
        printf("%lld\n", zeroes(n)-zeroes(m-1));
    }
    
    return 0;
}
