#include<stdio.h>

long gcd(long m, long n){
    long temp;
    
    while(n){
        temp=m; m=n; n=temp%n;
    }
    
    return m;
}

int main(){
    long g, a, b, c;
    
    while(scanf("%ld", &a)!=EOF && a){
        scanf("%ld", &c);
        g=c-a;
        while(scanf("%ld", &b)!=EOF && b){
            g=gcd(g,b-a);
            if(g<0) g=-g;
        }
        
        printf("%ld\n", g);
    }
    
    return 0;
}
