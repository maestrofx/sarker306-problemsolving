#include <stdio.h>

int main(){
    unsigned test, kase;
    long height[100005], max, y, n, i;
    
    while ( scanf("%d", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ) {
            scanf("%ld", &n);
            height[0] = 0;
            for ( i = 1, max = -1 ; i <= n ; i++ ){
                scanf("%ld", height + i );
                y = height[i] - height[i-1];
                if ( max < y ) max = y;
            }
            
            for ( i = 1, y = max; i <= n ; i++ ){
                if ( y + height[i-1] < height[i] ) break;
                if ( y == height[i] - height[i-1] ){
                   /* printf("%ld to %ld --> %ld\n", height[i-1], height[i], y-1);*/
                    y--;
                }
            }
            
            if ( i != n + 1 ) max++;
            printf("Case %ld: %ld\n", kase, max);
        }
    }
    
    return 0;
}
