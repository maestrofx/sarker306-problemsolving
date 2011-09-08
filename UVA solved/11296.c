#include<stdio.h>

int main(){
    long long n, x;
    
    while(scanf("%lld", &n)!=EOF){
        x=n/2+1;
        printf("%lld\n", (x*(x+1))/2);
    }
    
    return 0;
}
