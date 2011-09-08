#include <stdio.h>

double proba[21], p[21];

int countOne(long n){
    int i;
    
    for ( i = 0 ; n ; n &= ( n - 1 ), i++ );
        
    return i;
}

int main(){
    int n, r, kase = 1;
    unsigned long lim, i, musk, j;
    double sum, x;
    
    while( scanf("%d%d", &n, &r) == 2 && ( n || r )){
        for ( j = 0 ; j < n ; j++ ){
            scanf("%lf", &p[j] );
            proba[j] = 0;
        }
        
        for ( i = 0, sum = 0, lim = 1 << n ; i < lim ; i++ ){
            if ( countOne(i) == r ){
                for ( j = 0, x = 1, musk = 1 ; j < n ; j++, musk <<= 1 ){
                    if ( i & musk ) x *= p[j];
                    else x *= 1 - p[j];
                }
                
                sum += x;
                for ( j = 0, musk = 1 ; j < n ; j++, musk <<= 1 ){
                    if ( i & musk ) proba[j] += x;
                }
            }
        }
        
        printf("Case %d:\n", kase++);
        for ( j = 0 ; j < n ; j++ ) printf("%.6lf\n", proba[j]/sum);
    }
    
    return 0;
}
