#include <cstdio>
#include <cmath>
#include <set>
#include <cstdlib>
#define SIZE 1000002LL
#define SQRTSIZE 1001
#define MAXFACTORS 20000
#define PRIMESTOSIZE 78500

long arrPhi[SIZE], primes[PRIMESTOSIZE], numberOfPrimes, numberOfFactors;
char isNotPrime[SIZE];
long long arr[MAXFACTORS+2];
typedef struct{
    long long factor, phiVal;
}FactorsWithPhi;

FactorsWithPhi factorswithphi[MAXFACTORS + 1];
using namespace std;

void initArrays(){
    long i, j;
    
    for ( i = 0 ; i < SIZE ; i++ ) arrPhi[i] = i;
    for ( i = 2 ; i < SIZE ; i+=2 ) arrPhi[i] >>= 1;
    
    primes[numberOfPrimes++] = 2;
    for ( i = 3 ; i < SIZE ; i+=2 ){
        if ( isNotPrime[i>>1] == 0 ){
            if ( i < SQRTSIZE )
                for ( j = i * i ; j < SIZE ; j += i<<1 )
                    isNotPrime[j>>1] = 1;
            
            primes[numberOfPrimes++] = i;
            for ( j = i ; j < SIZE ; j+=i )
                arrPhi[j] -= arrPhi[j]/i;
        }
    }
}

long lowerBound(long long num ){
    long low = 0, high = numberOfFactors, mid;
    
    while ( low + 1 < high ) {
        mid = ( low + high ) >> 1;
        if ( factorswithphi[mid].factor > num ) high = mid;
        else low = mid;
    }
    
    return low;
}

int cmp(const void *a, const void *b){
    FactorsWithPhi *x = (FactorsWithPhi*)a, *y = (FactorsWithPhi*)b;
    
    if ( x->factor < y->factor ) return -1;
    else return 1;
}

void factorizeBFS(long long n){
    long head = 0, tail = 0, i, k = 0, lim = (long)(sqrt(n) + 0.5);
    long long m = n, x;
    long long primeFactor[50];
    FactorsWithPhi u, v;
    set<long long>isVisited;
    
    for ( i = 0 ; i < numberOfPrimes && primes[i] <= lim ; i++ ){
        if ( m % primes[i] == 0 ){
            do{
                m /= primes[i];
            }while ( m % primes[i] == 0 );
            primeFactor[k++] = primes[i];
            lim = (long)(sqrt(m) + 0.5);
        }
    }
    
    if ( m > 1 ) primeFactor[k++] = m;
    
    isVisited.insert(1);
    u.factor = 1, u.phiVal = 1;
    factorswithphi[tail++] = u;
    while ( head != tail ){
        u = factorswithphi[head++];
        
        for ( i = 0 ; i < k ; i++ ){
            x = primeFactor[i];
            if ( x <= n/u.factor && n%(u.factor * x) == 0 ){
                v.factor = u.factor * x;
                if ( isVisited.find(v.factor) == isVisited.end() ){
                    if ( v.factor < SIZE ) v.phiVal = arrPhi[v.factor];
                    else if ( u.factor % x == 0 ) v.phiVal = u.phiVal * x;
                    else v.phiVal = u.phiVal * ( x - 1 );
                    factorswithphi[tail++] = v;
                    isVisited.insert(v.factor);
                }
            }
        }
    }
    
    factorswithphi[tail].factor = 1LL<<62;
    numberOfFactors = tail;
    qsort( factorswithphi, tail, sizeof(FactorsWithPhi), cmp);
}

void precalculateNumbersForQueries(long long n){
    long i, j;
    
    numberOfFactors = 1;
    factorizeBFS(n);
    arr[0] = factorswithphi[numberOfFactors - 1].phiVal;
    for ( i = 1, j = numberOfFactors - 2 ; i < numberOfFactors ; i++, j-- ){
        arr[i] = arr[i-1] + factorswithphi[j].phiVal;
    }
    
    arr[i] = arr[i-1]; /* dummy, used in case input x > n */
}

int main(){
    long long n, x;
    long query, kase, tests;
    
    initArrays();
    scanf("%ld", &tests);
    for( kase = 1 ; kase <= tests ; kase++ ){
        scanf("%lld", &n);
        precalculateNumbersForQueries(n);
        printf("Case %ld\n", kase);
        scanf("%ld", &query);
        while( query-- ){
            scanf("%lld", &x);
            if ( x < 1 ){
                printf("0\n");
                continue;
            }
            printf("%lld\n", arr[lowerBound(x)]);
        }
    }
    
    return 0;
}
/* test with 200560490130 */
