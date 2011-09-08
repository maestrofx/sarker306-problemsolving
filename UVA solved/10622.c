#include <stdio.h>
#include <math.h>

int main(){
    long x, i, y, m, pp, n;
    double logy, mm;
    
    while ( scanf("%lld", &x) != EOF && x ){
        y = x > 0 ? x : -x;
        logy = log10(y);
        for ( i = 2, pp = 1 ; i < 33 ; i++ ){
            m = mm = pow(10, logy / i) + 1e-6;
            if ( m < 2 ) break;
           // printf("%lf %ld\n", mm, m);
            for ( n = 1, y = m ; n < i ; n++, y *= m);
            if ( y == x ){
                pp = i;
                //printf("    pp = %ld\n", pp);
            }
            if( x < 0 ){
                for ( n = 1, y = -m ; n < i ; n++, y *= -m);
                if ( y == x ){
                    pp = i;
                    //printf("    pp = %ld\n", pp);
                }
            }
        }
        
        printf("%ld\n", pp);
    }
    
    return 0;
}
