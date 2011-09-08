#include<stdio.h>

int main(){
    char num[1005], num2[15], base;
    long x, i, mod;
    
    while(scanf("%d", &base) != EOF && base>0){
        scanf("%s%s", num, num2);
        for(i = x = 0; num2[i] ; i++ ) x = base * x + num2[i] - '0' ;
        for(i = mod = 0 ; num[i] ; i++ ) mod = ( base * mod + num[i] - '0' ) % x;
        for(i = 0 ; mod ; mod /= base ) num2[i++] = mod % base + '0' ;
        if( i == 0) num2[i++] = '0';
        for( ; i ; ) putchar(num2[--i]);
        puts("");
    }
    
    return 0;
}
