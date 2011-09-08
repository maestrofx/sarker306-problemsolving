#include<stdio.h>

typedef long long llong;

llong gcd(llong m, llong n){
    llong temp;
    
    if(m<n) m^=n^=m^=n;
    while(n){ temp=m ; m=n;  n=temp%n; }
    return m;
}

int main(){
    int test, count, i, j;
    llong array[200], x, max;
    char ch;
    
    while(scanf("%d", &test)!=EOF){
        while((ch=getchar())!='\n');
        while(test--){
            count=x=max=0;
            while((ch=getchar())!='\n'){
                if((ch<'0' || ch>'9') && x){
                    array[count++]=x;
                    x=0;
                }
                else if(ch>='0' && ch<='9') x=10*x+ch-'0';
            }
            if(x) array[count++]=x;
            
            for(i=0, x=0;i+1<count;i++){
                for(j=i+1;j<count;j++){
                    x=gcd(array[i], array[j]);
                    max=(max>x)?max:x;
                }
            }
            
            printf("%lld\n", max);
        }
    }
    
    return 0;
}
