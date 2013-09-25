#include <stdio.h>
#define SIZE 102

void printMatrix( char arr[][SIZE], int size ){
    int i, j;
    
    for ( i = 1 ; i <= size ; i++ ){
        for ( j = 1 ; j <= size ; j++ )
            putchar(arr[i][j] + '0');
        puts("");
    }
}
    
void calcReachableMatrix( char next[][SIZE], char now[][SIZE], char base[][SIZE], int n ){
    char tmp[SIZE][SIZE];
    int i, j, k;
    
    for ( i = 1 ; i <= n ; i++ )
        for ( j = 1 ; j <= n ; j++ ){
            tmp[i][j] = 0;
            
            for ( k = 1 ; k <= n ; k++ ) tmp[i][j] |= ( now[i][k] & base[k][j] );
        }
    
    for ( i = 1 ; i <= n ; i++ )
        for ( j = 1 ; j <= n ; j++ )
            next[i][j] = tmp[i][j];
}

void calcReachabilityInStep( char res[SIZE][SIZE], char base[][SIZE], int size, int days ){
    char tmp[SIZE][SIZE];
    int i, j;
    
    for ( i = 1 ; i <= size ; i++ )
        for ( j = 1 ; j <= size ; j++ ) 
            tmp[i][j] = base[i][j];
    
    for ( i = 1 ; i <= size ; i++ ) res[i][i] = 1;
    i = 1;
    while ( days ){
        if ( days & 1 ) calcReachableMatrix( res, res, tmp, size );
        calcReachableMatrix( tmp, tmp, tmp, size );
        days >>= 1;
    }
}

int main(){
    int c, l, u, v, s, e, d;
    char base[SIZE][SIZE], res[SIZE][SIZE];
    
    while ( scanf("%d%d", &c, &l) == 2 ){
        if ( c == 0 && l == 0 ) break;
        
        for ( u = 1 ; u <= c ; u++ )
            for ( v = 1 ; v <= c ; v++ )
                base[u][v] = 0, res[u][v] = 0;
                
        while ( l-- ){
            scanf("%d%d", &u, &v);
            base[u][v] = base[v][u] = 1;
        }
        
        scanf("%d%d%d", &s, &e, &d);
        calcReachabilityInStep( res, base, c, d );
        if ( res[s][e] ) puts("Yes, Teobaldo can travel.");
        else puts("No, Teobaldo can not travel.");
    }
    
    return 0;
}
