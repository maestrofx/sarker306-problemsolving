#include <stdio.h>
#define SIZE 10000001

double cache[SIZE];
#define MAXSIEVE SIZE
#define MAXSIEVEHALF (MAXSIEVE/2)
#define MAXSQRT 5000 /* sqrt(MAXSIEVE)/2*/
char a[MAXSIEVE/16+2];
#define isprime(n) (a[(n)>>4]&(1<<(((n)>>1)&7))) /* Works when n is odd*/

long primes[SIZE/8], primeCnt;

double calcProbability( long n ){
    long i, undiv = 0;
    double res = 0;
    /*printf(" in %ld\n", n);*/
    if ( n == 1 ) return 0;
    if ( cache[n] ) return cache[n];
    for ( i = 0 ; primes[i] <= n ; i++ ){
        if ( n % primes[i] ) undiv++;
        else res += 1 + calcProbability( n / primes[i] )/*, printf("%ldth prime %ld divides %ld\n", i, primes[i], n)*/;
    }
    
    /*puts("hmm");*/
    res = res / i + undiv * 1.0 / i;
    cache[n] = i * res / ( i - undiv );
    /*printf("%ld primes upto %ld, %ld dont divide... res = %lf, cache= %lf\n", i, n, undiv, res, cache[n]);*/
    return cache[n];
}

void initPrimes(){
    long i, j;
    
    memset(a,255,sizeof(a));
    a[0] = 0xFE;
    for ( i = 1 ; i <= MAXSQRT ; i++ )
        if ( a[i>>3] & (1<<(i&7) ) )
        for ( j = i + i + i + 1 ; j < MAXSIEVEHALF ; j += i+i+1 )
            a[j>>3] &= ~(1<<(j&7));
    
    primes[primeCnt++] = 2;
    for ( i = 3 ; i < SIZE ; i += 2 )
        if ( isprime(i) ) primes[primeCnt++] = i;
}

int main(){
    int test, kase;
    long n;
    
    initPrimes();
   /* for ( n = 1 ; n < SIZE ; n++ ){
        printf("%ld\n", n);
        calcProbability(n);
    }*/
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld", &n);
            printf("Case %d: %.10lf\n", kase, calcProbability(n));
        }
    }
    
    return 0;
}
