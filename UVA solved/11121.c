#include<stdio.h>

int main(){
    long test, i, n, base=-2, j, quo, rem;
    char output[100];
    
    while(scanf("%ld", &test)!=EOF){
        for(i=1;i<=test;i++){
            scanf("%ld", &n);
            printf("Case #%ld: ", i);
            
            for(j=0;n;j++, n=quo){
                quo=n/base;
                rem=n%base;
                if(rem<0) quo++, rem=-rem;
                output[j]=rem+'0';
            }
            
            if(j==0) putchar('0');
            else for(--j;j>=0;j--) putchar(output[j]);
            puts("");
        }
    }
    
    return 0;
}
