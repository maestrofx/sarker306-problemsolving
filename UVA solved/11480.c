#include<stdio.h>

int main(){
    long long n, x, i, j, flag=1;
    
    while(scanf("%lld", &n)!=EOF){
        if(n==0) break;
        
        for(x=0, i=1; ; i++){
            j=((n-i)-!((n-i)%2))/2 - i;
            if(j<=0) break;
            x+=j;
        }
        
        printf("Case %lld: %lld\n", flag++, x);
    }
    
    return 0;
}
