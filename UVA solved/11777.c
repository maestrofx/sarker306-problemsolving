#include<stdio.h>

int main(){
    long test, i, j, min, a, b, c, x, sum;
    
    while(scanf("%ld", &test)!=EOF){
        for(i=1;i<=test;i++){
            for(j=0, sum=0;j<4;j++){
                scanf("%ld", &x);
                sum+=x;
            }
            scanf("%ld", &a);
            scanf("%ld", &b);
            scanf("%ld", &c);
            min=(a<b)?a:b;
            min=(min<c)?min:c;
            sum+=(a+b+c-min)/2;
            printf("Case %ld: ", i);
            if(sum>=90) printf("A");
            else if(sum>=80) printf("B");
            else if(sum>=70) printf("C");
            else if(sum>=60) printf("D");
            else printf("F");
            puts("");
        }
    }
    
    return 0;
}
