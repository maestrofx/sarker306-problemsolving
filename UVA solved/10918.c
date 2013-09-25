#include <stdio.h>

typedef unsigned long _ull;

_ull config[33][3][8];
char visited[33][3][8];

_ull backtrack( int row, int col, int conf ){
    if ( row == 0 && conf == 0 ) return 1;
    if ( row == 0 ) return 0;
    if ( col == 3 ) return backtrack( row - 1, 0, conf);
    if ( visited[row][col][conf] ) return config[row][col][conf];
    
    visited[row][col][conf] = 1;
    if ( conf & ( 1 << col ) )
        return config[row][col][conf] = backtrack( row, col + 1, conf & (~(1<<col)) );
    
    config[row][col][conf] = 0;
    config[row][col][conf] += backtrack( row, col + 1, conf | ( 1 << col ) );
    if ( col < 2 && !( conf & ( 1 << ( col + 1 )))) config[row][col][conf] += backtrack( row, col + 2, conf );
    
    return config[row][col][conf];
}

int main(){
    int n;
    
    while( scanf("%d", &n) != EOF && n >= 0 )
        printf("%lu\n", backtrack(n, 0, 0));
       
    return 0;
}
