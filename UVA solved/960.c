#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

#define LIM  10001
char sieve[LIM];
long primes[LIM], ind;

int isPrime(int n){
	int i;
	
	if ( n < LIM ) return !sieve[n];
	for ( i = 0 ; i < ind ; i++ ) if ( n % primes[i] == 0 ) return 0;
	return 1;
}

int isGaussianPrime(long x, long y){
	if ( x == 1 && y == 1 ) return 0;
	if ( x == 0 ) return isPrime(y) && (y % 4 == 3);
	if ( y == 0 ) return isPrime(x) && (x % 4 == 3);
	if ( isPrime(x*x + y*y) && (x*x + y*y) % 4 != 3 ) return 1;
	return 0;
}

int main(){
	long i, j;
	int test;

	for ( i = 4 ; i < LIM ; i += 2 ) sieve[i] = 1;
	for ( i = 3 ; i < LIM ; i += 2 )
		if ( sieve[i] == 0 )
			for ( j = i * i ; j < LIM ; j += i ) sieve[j] = 1;

	for ( i = 2 ; i < LIM ; i++ ) if ( sieve[i] == 0 ) primes[ind++] = i;
	
	while ( scanf("%d", &test) == 1 ){
		while ( test-- ){
			scanf("%ld%ld", &i, &j);
			if ( i < 0 ) i = -i;
			if ( j < 0 ) j = -j;
			if ( isGaussianPrime(i, j) ) putchar('P');
			else putchar('C');
			puts("");
		}
	}
	
	return 0;
}

