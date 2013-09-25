#include <stdio.h>
#define SIZE 20002

int coins[105], change[2*SIZE+2], nCoins, curCoin[2*SIZE+2];

void result(int endPos){
    int i, j, max = 1 << 14, lim, incLim = 0;
    
    for ( i = 1, lim = 0 ; i <= nCoins ; i++ ) if ( lim < coins[i] ) lim = coins[i];
    lim += endPos;
    
    for ( i = 1 ; i <= lim ; i++ ) change[i] = max, curCoin[i] = -1;
    change[0] = 0;
    for ( i = 1 ; i <= nCoins ; i++ ){
        for ( j = lim ; j >= coins[i] ; j-- ) {
            if ( curCoin[j-coins[i]] != i && change[j] > change[j-coins[i]] + 1 ) {
                change[j] = change[j-coins[i]] + 1/*, printf("%d ", j)*/;
                curCoin[j] = i;
            }
        }
        /*puts("");*/
    }
    
    for ( ; change[endPos] == max ; endPos++ );
    printf("%d %d\n", endPos, change[endPos]);
}

int main(){
    int test, des, i;
    
    while ( scanf("%d", &test) != EOF ){
        while ( test-- ){
            scanf("%d", &des);
            scanf("%d", &nCoins);
            
            for ( i = 1 ; i <= nCoins ; i++ ) scanf("%d", coins + i );
            result(des);
        }
    }
    
    return 0;
}
