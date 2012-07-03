#include <stdio.h>

char residueModTen[10][6]={ { 0 },
                        { 1 },
                        { 6, 2, 4, 8, 6 },
                        { 1, 3, 9, 7, 1 },
                        { 6, 4, 6 },
                        { 5 },
                        { 6 },
                        { 1, 7, 9, 3, 1 },
                        { 6, 8, 4, 2, 6 },
                        { 1, 9, 1 } };
char residueCycle[10] = { 1, 1, 4, 4, 2, 1, 1, 4, 4, 2 };

void zero_cancel(char *A){
	int zero = 0, i, j;

	while ( A[zero] == '0' ) zero++;
	if ( zero ) for ( i = zero , j = 0 ; A[ i - 1 ] != '\0' ; i++, j++ )
        A[j] = A[i];
    
    if ( A[0] == 0 ) A[1] = 0, A[0] = '0';
}

int main(){
    char a[105], b[105], i, lastDigitOfA, x;
    
    while( scanf("%s%s", &a, &b) != EOF ){
        if ( a[0] == '0' && b[0] == '0' ) break;
        for ( i = 0 ; a[i] != 0 ; i++ ) lastDigitOfA = a[i] - '0';
        for ( i = 0 ; b[i] != 0 ; i++ ) x = b[i] - '0';
        if ( i > 1 ) x += 10 * ( b[i-2] - '0' );
        
        if ( b[0] == '0' ) puts("1");
        else printf("%d\n", residueModTen[lastDigitOfA][x % residueCycle[lastDigitOfA]]);
    }
    
    return 0;
}
