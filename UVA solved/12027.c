#include <stdio.h>
#include <string.h>

char a[1005];
char xx[100];

int main(){
    int x, y;
    
    for( x = 1 ; x < 10 ; x++ ) xx[x*x] = x;
    for( x = 2, y = 1 ; x < 100 ; x++ ){
        if( xx[x] == 0 ) xx[x] = y;
        else y = xx[x];
    }
    
    while ( scanf("%s", a) != EOF ){
        if (a[0] == '0' && a[1] == 0 ) break;
        x = a[0] - '0';
        if( (y = strlen(a)) % 2 == 0 ) x = 10 * x + a[1] - '0';
        printf("%d", xx[x]);
        y++;
        for( x = 01, y >>= 1 ; x < y ; x++ ) putchar('0');
        puts("");
    }
    
    return 0;
}
