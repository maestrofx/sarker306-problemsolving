#include <stdio.h>

typedef unsigned long long u64;

void int_str_mult(char *A, int n, char *B){
    int carry=0, i, x, j, prod;
    char p[10]={0};
    x=strlen(A);
    for(i=x-1; i+1;i--){
        prod=(A[i]-'0')*n+carry;
        B[i]=prod%10+'0';
        carry=prod/10;
    }
    if(carry){
        prod=carry;
        for(j=0;prod;j++, prod/=10) p[j]=prod%10+'0';
        for(i=x;i+1;i--) B[i+j]=B[i];
        j--;
        for(i=0;j>=0;j--, i++) B[i]=p[j];
    }
}

char power3[65][80];

int main(){
    u64 limit = ~0, x;
    char i, printFlag;
    
    power3[0][0] = '1';
    for ( i = 1 ; i < 65 ; i++ )
        int_str_mult( power3[i-1], 3, power3[i]);
    
    while ( scanf("%llu", &x) != EOF && x ){
        putchar('{');
        x--;
        for ( printFlag = i = 0 ; x ; x >>= 1, i++ )
            if ( x & 1 ){
                if ( printFlag ) putchar(',');
                printFlag = 1;
                printf(" %s", power3[i]);
            }
        
        puts(" }");
    }
    
    return 0;
}
