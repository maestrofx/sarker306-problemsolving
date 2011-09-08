#include <stdio.h>

long long cheby[51][51];

void print_cheby(int n){
    int i, sign;
    long long x;

    printf("%lldCos^%d(A)", cheby[n][n], n);
    for( i = n - 1 ; i > 1 ; i-- ){
        if( cheby[n][i] != 0 ){
            sign = '+';
            x = cheby[n][i];
            if( x < 0 ) sign = '-', x = -x;
            printf("%c%lldCos^%d(A)", sign, x, i);
        }
    }

    if( cheby[n][1] != 0 ){
        sign = '+';
        x = cheby[n][1];
        if( x < 0 ) sign = '-', x = -x;
        printf("%c%lldCos(A)", sign, x);
    }

    if(cheby[n][0] != 0){
        sign = '+';
        x = cheby[n][0];
        if( x < 0 ) sign = '-', x = -x;
        printf("%c%lld", sign, x);
    }

    puts("");
}

void init(){
    int i, j;

    cheby[0][0] = 1;
    cheby[1][0] = 0, cheby[1][1] = 1;

    for( i = 2 ; i <= 50 ; i++ ){
        for( j = 0 ; j < i ; j++ )
            cheby[i][j + 1] = 2 * cheby[i-1][j];
        for( j = 0 ; j < i ; j++ ) cheby[i][j] -= cheby[i-2][j];
    }
}

int main(){
    int n;

    init();

    while( scanf("%d", &n) != EOF && n > 0)
        if( n == 1 ) puts("Cos(A)");
        else print_cheby(n);

    return 0;
}
