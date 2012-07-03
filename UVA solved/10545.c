#include <stdio.h>
#include <math.h>
#include <assert.h>
#define EPS 1e-6
#define EPSFUN 1e-6

double peri, a, b, x, y;

double rad(double theta){
    double r, phi, z = sqrt(a*a+b*b-2*a*b*cos(2*theta));
    
    phi = 0.5*( asin(a*sin(2*theta)/z) + acos((z*z+x*x-y*y)/(2*z*x)) );
    r = b*tan(theta)*tan(phi)/(tan(theta)+tan(phi));
    
    return r;
}

double ternaryMax(double thetaA, double thetaC, double (*f)(double)){
    double theta2 = ( thetaA + 2 * thetaC ) / 3, theta1 = ( 2 * thetaA + thetaC ) / 3, tmp;

    if( fabs(thetaA - thetaC) < EPSFUN ) return (thetaA+thetaC)/2;
    if(f(theta1) < f(theta2))
        return ternaryMax(theta1, thetaC, f);
    else return ternaryMax(thetaA, theta2, f);
}

void calcMaxRad(long P, long A, long B){
    if ( A > B ) A ^= B ^= A ^= B;
    peri = P, a = A, b = B;
    x = peri / 2 - a, y = peri / 2 - b;
    
    if ( A <=0 || B <= 0 || peri<= 0 || fabs(x) < EPS || fabs(y) < EPS || x < 0 || y < 0 ){
        puts("Eta Shombhob Na.");
        return ;
    }
    
    /*printf("%.6lf\n", sqrt(a*b*x*y)/(a+x));*/
    printf("%.6lf\n", x=rad(ternaryMax(0, acos(0), rad)));
}

int main(){
    long P, A, B, test, kase;
    
    scanf("%ld", &test);
    for ( kase = 1 ; kase <= test ; kase++ ){
        scanf("%ld%ld%ld", &P, &A, &B);
        printf("Case %ld: ", kase);
        calcMaxRad(P,A,B);
    }

    return 0;
}
/*
365 154 89
350 155 90
400 180 90
*/
