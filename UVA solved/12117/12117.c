#include <stdio.h>

int n, kase;
long long ways[2001][8][8][8];
int visited[2001][8][8][8];
long long cached[2001];

long long calcWays( int curRow, int rowconf, int nextconf, int thenconf ){
    long long ans = 0;
    
    /*printf("%d %d %d %d\n", curRow, rowconf, nextconf, thenconf);*/
    if ( rowconf == 0 && nextconf == 0 && thenconf == 0 && cached[n-curRow-1] )
        return cached[n-curRow-1];
    if ( curRow == n && rowconf == 0 && nextconf == 0 && thenconf == 0 ) return 1;
    if ( curRow >= n ) return 0;
    if ( visited[curRow][rowconf][nextconf][thenconf] == kase )
        return ways[curRow][rowconf][nextconf][thenconf];
    
    visited[curRow][rowconf][nextconf][thenconf] = kase;
    
    /* piece 1 */
    if ( rowconf == 0 )
        ans += calcWays(curRow + 1, nextconf, thenconf, 0);

    /* piece 2 */
    if ( rowconf == 0 && !(nextconf & 2) )
        ans += calcWays(curRow + 1, nextconf | 2, thenconf, 0);

    /* piece 3 */
    if ( rowconf == 2 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0);

    /* piece 4 */
    if ( rowconf == 1 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0);
    
    /* piece 5 */
    if ( rowconf == 5 && nextconf == 0 && !(thenconf & 2) )
        ans += calcWays( curRow + 1, 7, thenconf | 2, 0);
        
    /* piece 6 */
    if ( rowconf == 0 && !(nextconf & 5) )
        ans += calcWays( curRow + 1, nextconf | 5, thenconf, 0);
    
    /* piece 7 */
    if ( rowconf == 5 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0 );
    
    /* piece 8 */
    if ( rowconf == 3 && !(nextconf & 6) && !(thenconf & 3) )
        ans += calcWays( curRow + 1, nextconf | 6, thenconf | 3, 0);
    
    /* piece 9 */
    if ( rowconf == 6 && !(nextconf & 3) && !(thenconf & 6) )
        ans += calcWays( curRow + 1, nextconf | 3, thenconf | 6, 0);
    
    /* piece 10 */
    if ( rowconf == 1 && !(nextconf & 3) )
        ans += calcWays( curRow + 1, nextconf | 3, thenconf, 0);
    
    /* piece 11 */
    if ( rowconf == 4 && !(nextconf & 6) )
        ans += calcWays( curRow + 1, nextconf | 6, thenconf, 0);
    
    /* piece 12 */
    if ( rowconf == 0 && !(nextconf & 3) )
        ans += calcWays( curRow + 1, nextconf | 3, thenconf, 0);
    
    /* piece 13 */
    if ( rowconf == 4 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0);
    
    /* piece 14 */
    if ( rowconf == 0 && !(nextconf & 1) )
        ans += calcWays( curRow + 1, nextconf | 1, thenconf, 0 );
    
    /* piece 15 */
    if ( rowconf == 6 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0 );
    
    /* piece 16 */
    if ( rowconf == 1 && !(nextconf & 3) && !(thenconf & 1) )
        ans += calcWays( curRow + 1, nextconf | 3, thenconf | 1, 0 );
    
    /* piece 17 */
    if ( rowconf == 4 && !(nextconf & 6) && !(thenconf & 4) )
        ans += calcWays( curRow + 1, nextconf | 6, thenconf | 4, 0 );
    
    /* piece 18 */
    if ( rowconf == 0 && !(nextconf & 4) )
        ans += calcWays( curRow + 1, nextconf | 4, thenconf, 0 );
    
    /* piece 19 */
    if ( rowconf == 3 && nextconf == 0 )
        ans += calcWays( curRow + 1, 7, thenconf, 0 );
    
    /* piece 20 */
    if ( rowconf == 6 && nextconf == 0 && !(thenconf & 1) )
        ans += calcWays( curRow + 1, 7, thenconf | 1, 0 );
    
    /* piece 21 */
    if ( rowconf == 3 && nextconf == 0 && !(thenconf & 4) )
        ans += calcWays( curRow + 1, 7, thenconf | 4, 0 );
    
    /* piece 22 */
    if ( rowconf == 0 && !(nextconf & 6) )
        ans += calcWays( curRow + 1, nextconf | 6, thenconf, 0);
    
    if ( rowconf == 7 ) ans += calcWays( curRow + 1, nextconf, thenconf, 0);
    
    ans %= 1000000000000LL;
    if ( rowconf == 0 && nextconf == 0 && thenconf == 0 )
        cached[n-curRow-1] = ans;

    return ways[curRow][rowconf][nextconf][thenconf] = ans;
}

int main(){
    while ( scanf("%d", &n)== 1 && n > 0 ){
        ++kase;
        printf("Case %d: %lld\n", kase, calcWays(0,0,0,0));
    }
    
    return 0;
}
