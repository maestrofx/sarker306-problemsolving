#include<stdio.h>
#include<math.h>

long mod(long n, long k, long m){
    long x;
    if(k == 0) return 1;
    if( k & 1) x = (mod(n, k - 1, m) * n) % m;
    else{
        x = mod(n, k>>1, m);
        x *= x;
        x %= m;
    }

    return x;
}

int main(){
    int test;
    long n, k;
    double x;

    while(scanf("%d", &test) != EOF){
        while(test-- > 0){
            scanf("%ld%ld", &n, &k);
            x = k * log10(n);
            x = pow( 10 , x - (long)x);
            printf("%ld...%03ld\n", (long)(x*100), mod(n, k, 1000));
        }
    }

    return 0;
}
