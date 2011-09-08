#include<stdio.h>

int main(){
    int test, n, x, min, max;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &n); max=0, min=1000;
            while(n--){
                scanf("%d", &x);
                if(max<x) max=x;
                if(min>x) min=x;
            }
            
            printf("%d\n", (max-min)*2);
        }
    }
    
    return 0;
}
