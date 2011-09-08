#include<stdio.h>

int main(){
    long N;
    
    while(scanf("%ld", &N)!=EOF && N>=0){
        if(N>1) printf("%ld%%\n", (long)(N*25));
        else printf("0%%\n");
    }
    
    return 0;
}
