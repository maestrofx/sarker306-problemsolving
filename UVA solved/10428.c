#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159
#define EPS 1e-10

int cmp(const void *a, const void *b){
    if( fabs(*(double*)a - *(double*)b) < EPS ) return 0;
    if( *(double*)a > *(double*)b ) return 1;
    return -1;
}

void synthetic_div(double *coeff, int n, double a){
    int i;

    for ( i = n - 1 ; i >= 0 ; i-- ) coeff[i] = coeff[i] + a * coeff[i+1];
    for( i = 0 ; i < n ; i++ ) coeff[i] = coeff[i + 1];
}

void function_derivative(double *coeff, int n, double x, double *p, double *dp){
	int i;

    *p = coeff[n], *dp = 0;
	for( i = n - 1 ; i >= 0 ; i-- ){
	    *dp = *dp * x + *p;
	    *p = *p * x + coeff[i];
	}
}

int newtonraphson(double *coeff, int n, double x, double *ptrx){
    double f, f1;
    int loopcount = 0;

    do{
        if(loopcount == 30) return 0;
        *ptrx = x;
        function_derivative(coeff, n, x, &f, &f1);
        if( fabs(f1) < EPS ) return 0;
        x = x - f / f1;
        loopcount++;
    }while( fabs(x - *ptrx) > EPS);

    return 1;
}

void root_find(double *coeff, int n, double *roots){ /* all roots real! */
    double i, a1, a2, b1, b2, x;
    int j;

    for( j = 0 ; j < n ; j++ ){
        for( i = 3 * PI ; i < 25.1 ; i = i + .25 ){
            if (newtonraphson(coeff, n - j, i, &x) == 1)
            break;
            if (newtonraphson(coeff, n - j, -i, &x) == 1)
            break;
        }

        roots[j] = x;
        synthetic_div(coeff, n - j, x);
        /*printf("root = %.3lf\n", x);*/
    }

    qsort(roots, n, sizeof(double), cmp);
}

int main(){
    int n, i, kase = 1;
    double coeff[7], roots[7], a;

    while( scanf("%d", &n ) != EOF && n > 0 ){
        for ( i = n ; i >= 0 ; i-- ) scanf("%lf", coeff + i);
        for ( i = n - 1 ; i >= 0 ; i-- ) coeff[i] = coeff[i] / coeff[n];
        coeff[n] = 1;
        /*scanf("%lf", &a);
        synthetic_div(coeff, n, a);*/
        root_find(coeff, n, roots);
        printf("Equation %d:", kase++);
        for( i = 0 ; i < n ; i++ ) printf(" %.4lf", roots[i]);
        puts("");
    }

    return 0;
}
