#include<stdio.h>

int main(){
    long a, b, c, d, e, f, i, test;
    
    while(scanf("%ld", &test)!=EOF){
        for(i=1;i<=test;i++){
            scanf("%ld%ld%ld", &a, &b, &c);
            d=a;
            d=(d>b)?d:b;
            d=(d>c)?d:c;
            e=a;
            e=(e<b)?e:b;
            e=(e<c)?e:c;
            printf("Case %ld: %ld\n", i, a+b+c-d-e);
        }
    }
    
    return 0;
}
