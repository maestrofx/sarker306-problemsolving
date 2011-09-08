#include<stdio.h>
#define SIZE 10001

long array[SIZE+5];

void reset(void){
    int i;
    
    for(i=0;i<=SIZE;i++) array[i]=0;
}

int main(){
    long N, Q, i, x, test=0;
    
    while(scanf("%ld%ld", &N, &Q)!=EOF){
        if(N==0 && Q==0) break;
        
        for(i=0;i<N;i++){
            scanf("%ld", &x);
            array[x]++;
        }
        
        for(i=1;i<SIZE;i++) array[i]+=array[i-1];
        
        printf("CASE# %ld:\n", ++test);
        for(i=0;i<Q;i++){
            scanf("%ld", &x);
            if(array[x]==array[x-1]) printf("%ld not found\n", x);
            else printf("%ld found at %ld\n", x, array[x-1]+1);
        }
        
        reset();
    }
    
    return 0;
}
