#include<stdio.h>

int main(){
    int n, x[]={0,2,3,5,6,8} , ans;
    
    while(scanf("%d", &n)!=EOF){
        n--;
        printf("%d\n", 10+(n/6-1)*9+x[n%6]);
    }
    
    return 0;
}
