#include<stdio.h>
#define SIZE 1000001

long long ans[SIZE];

int main(){
    long long n, m;
    int test;
    
    ans[4] = 1;
    for( n = 5 ; n < SIZE ; n++ ){
        m = (n & 1)? (n-1)>>1 : n>>1;
        ans[n] = ans[n-1] + (n-m)*m + 1 - n;
    }
    
    while(scanf("%lld", &n)!=EOF){
        if( n < 3 ) break;
        printf("%lld\n", ans[n]);
    }
    
    return 0;
}
