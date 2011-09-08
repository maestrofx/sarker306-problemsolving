#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159
#define EPS 1e-10

long loopz;

int cmp(const void *a, const void *b){
    if( fabs(*(double*)a - *(double*)b) < EPS ) return 0;
    if( *(double*)a > *(double*)b ) return -1;
    return 1;
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
        if(loopcount == 15) return 0;
        *ptrx = x;
        function_derivative(coeff, n, x, &f, &f1);
        if( fabs(f1) < EPS ) return 0;
        x = x - f / f1;
        loopcount++;
        loopz++ ;
    }while( fabs(x - *ptrx) > EPS);

    return 1;
}

void root_find(double *coeff, int n, double *roots){ /* all roots real! */
    double i, a1, a2, b1, b2, x;
    int j;

    if(n == 1){
        roots[0] = coeff[1] / coeff[0];
    }
    else if( n == 0){
        b1 = 2 * coeff[2];
        i = sqrt( coeff[1] * coeff[1] - 4 * coeff[0] * coeff[2] ) / b1;
        a1 = -coeff[1] / b1;
        roots[0] = a1 + i;
        roots[1] = a1 - i;
    }
    else for( j = 0 ; j < n ; j++ ){
        for( i = 3*PI ; i < 25.1 ; i = i + .25 ){
            if (newtonraphson(coeff, n - j, i, &x) == 1)
            break;
            if (newtonraphson(coeff, n - j, -i, &x) == 1)
            break;
            loopz += 2;
        }

        roots[j] = x;
        synthetic_div(coeff, n - j, x);
        /*printf("root = %.3lf\n", x);*/
    }

    qsort(roots, n, sizeof(double), cmp);
}

int main(){
    int n, i, test;
    double coeff[1000], roots[7], a;
    char arr[20];

    while( scanf("%d", &test ) != EOF && test > 0 ){
        while(test--){
            scanf("%d", &n);
            for ( i = n ; i >= 0 ; i-- ) scanf("%lf", coeff + i);
            for ( i = n - 1 ; i >= 0 ; i-- ) coeff[i] = coeff[i] / coeff[n];
            coeff[n] = 1;
            loopz = 0;
            for( i = n ; i > 2 ; i--) {
                scanf("%lf", &a);
                synthetic_div(coeff, i, a);
            }
            root_find(coeff, 2, roots);
            /*printf("%ld\n", loopz);
            printf("Equation %d:", kase++);*/
            for( i = 0 ; i < 2 ; i++ ){
                sprintf(arr, "%.1lf", roots[i]);
                if( strcmp( arr, "-0.0") == 0 ) strcpy( arr, "0.0");
                puts(arr);
            }
        }
    }

    return 0;
}
