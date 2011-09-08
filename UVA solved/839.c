#include<stdio.h>

int input(){
    long w1, d1, w2, d2;
    
    scanf("%ld%ld%ld%ld", &w1, &d1, &w2, &d2);
    if(w1==0) w1=input();
    if(w2==0) w2=input();
    
    if(w1==0 || w2==0) return 0;
    if(w1*d1==w2*d2) return w1+w2;
    return 0;
}

int main(){
    int test;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            printf("%s\n", input()?"YES":"NO");
            if(test) puts("");
        }
    }
    
    return 0;
}
