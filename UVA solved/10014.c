#include <stdio.h>

int main(){
    int test, kase, n, i;
    double sum, a0, a, ci, a1;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            if ( kase > 1 ) puts("");
            scanf("%d", &n);
            scanf("%lf%lf", &a0, &a);
            
            a1 = a + n*a0;
            for ( sum = 0, i = n ; i ; i-- ){
                scanf("%lf", &ci);
                sum += i*ci;
            }
            
            a1 = (a1 - 2*sum)/(n+1);
            printf("%.2lf\n", a1);
        }
    }
    
    return 0;
}
