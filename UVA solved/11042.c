#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932384626433832795
#define LOG230 9.0308998699194358564121668417348

int main(){
    int test;
    long long a, b, n;
    double ang, r, x;
    
    scanf("%d", &test);
    while(test--){
        scanf("%lld%lld", &a, &b);
        if( b < 0 ) b = -b;
        if( a < 0 ) a = -a;
       /* if( a == 0 ) printf("2\n");
        else if( b == 0 ) printf("1\n");
        else if( a == b ) printf("4\n");
        else{
            if( b < 0 ) b = -b;
            if( a < 0 ) a = -a;
            r = sqrt(a*a+b*b);
            ang = atan(b*1.0/a);
            x = PI/ang;
           /* printf("%.6lf %ld ", x, (long)x);
            if( fabs(x - (long)x) < 1e-5 ){
                n = (long)x;
                if( n*log(r) + log(cos(n*ang)) > LOG230 ){
                   /* printf("%.3lf ", n*log(r) + log(cos(n*ang)));
                    printf("TOO COMPLICATED\n");
                }
                else printf("%ld\n", n);
            }
            else printf("TOO COMPLICATED\n");
        }*/
        if( b == 0 ) puts("1");
        else if ( a == 0 ) puts("2");
        else if( a == b ){
            if( 4 * b*b*b*b > 1<<30 ){
                printf("TOO COMPLICATED\n");
            }
            else puts("4");
        }
        else puts("TOO COMPLICATED");
    }
    
    return 0;
}
