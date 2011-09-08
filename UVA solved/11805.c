#include<stdio.h>

int main(){
    int T, N, K, P, i;
    
    scanf("%d", &T);
    
    for(i=1;i<=T;i++){
        scanf("%d%d%d", &N, &K, &P);
        P%=N;
        P=(P+K)%N;
        if(P==0) P=N;
        printf("Case %d: %d\n", i, P);
    }
    
    return 0;
}
