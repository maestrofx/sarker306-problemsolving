#include <stdio.h>
#include <math.h>

int main(){
    double L, L1, n, c, x, xtmp, r;
    
    while ( scanf("%lf%lf%lf", &L, &n, &c) == 3 ){
        if ( L < 0 && n < 0 && c < 0 ) break;
        
        L1 = L*(1+n*c);
        if ( fabs(n*c) > 1e-10 ){
            xtmp = 1, x = 0;
            while ( fabs(x - xtmp) > 1e-10 ){
                x = xtmp;
                /*xtmp = L1/L*sin(x);*/
                xtmp = x - (L*x-L1*sin(x))/(L-L1*cos(x)); /* newton raphsoning the above formula */
            }
            
            r = L1/(2*x);
            printf("%.3lf\n", r - sqrt(r*r-L*L/4));
        }
        else printf("0.000\n");
    }
    
    return 0;
}
