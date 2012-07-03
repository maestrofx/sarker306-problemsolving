#include <stdio.h>
#include <math.h>

double r[25], k[25], t;
int n;

double _time(double run){
    int i;
    double minn = 1e300, xx;
    
    for ( i = 1 ; i < n ; i++ ) {
        xx = run/r[i] + (t-run)/k[i];
        if ( minn > xx ) minn = xx;
    }
    
    return (-run/r[n] - (t-run)/k[n] + minn)*3600;
}

double ternaryMax(double a, double b, double (*f)(double) ){
    double x1 = (2*a+b)/3, x2 = (a+2*b)/3;
    
   /* printf("#%lf -> %lf, %lf -> %lf\n", x1, _time(x1), x2, _time(x2));*/
    if ( fabs(a-b) < 1e-10 ) return (a+b)/2;
    if ( f(x1) < f(x2) ) return ternaryMax( x1, b, f);
    else return ternaryMax( a, x2, f);
}

double calcMaxTime(){
    return ternaryMax(0, t, _time);
}

int main(){
    long x;
    double xx;
    
    while ( scanf("%ld", &x) == 1 ){
        t = (double)x;
        scanf("%d", &n);
        for ( x = 1 ; x <= n ; x++ ) scanf("%lf%lf", r + x, k + x);
        xx = calcMaxTime();
        if ( _time(xx) >= 0 ) printf("The cheater can win by %ld seconds with r = %.2lfkm and k = %.2lfkm.\n", (long)(_time(xx) + 0.5 ), xx, t-xx);
        else printf("The cheater cannot win.\n");
    }
    
    return 0;
}
