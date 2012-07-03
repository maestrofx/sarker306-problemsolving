#include <stdio.h>

char adj[5][5] = {   {-1, 0, 1,-1, 2},
                    { 0,-1, 3,-1, 4},
                    { 1, 3,-1, 5, 6},
                    {-1,-1, 5,-1, 7},
                    { 2, 4, 6, 7,-1}
};
char sequence[10], level;
void backtrack(char u, unsigned char musk){
    char i, v;
    
    if ( level == 9 ) puts(sequence);
    else{
        for ( i = 0 ; i < 5 ; i++ ){
            v = adj[u][i];
            if ( v != -1 && (musk & ( 1 << v )) == 0 ){
                sequence[level++] = i + '1';
                backtrack(i, musk | ( 1 << v ) );
                sequence[level--] = 0;
            }
        }
    }
}

int main(){
    sequence[9] = 0;
    sequence[0] = '1';
    level = 1;
    backtrack(0, 0);
    return 0;
}
