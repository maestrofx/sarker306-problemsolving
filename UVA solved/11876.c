#include <stdio.h>
#define SIZE 1000000

long a[SIZE+1];
long sieve[SIZE+1];

int main(){
    long i, j, test, kase;

    for ( i = 1 ; i <= 1000 ; i++ ){
        for ( j = i*i; j <= SIZE ; j += i )
            sieve[j] += 2;
            
        sieve[i*i]--;
    }
    
    for ( i = 1 ; i <= SIZE ; i += sieve[i] ) a[i] = 1;
    for ( i = 1 ; i <= SIZE ; i++ ) a[i] += a[i-1];
    
    while ( scanf("%ld", &test) != EOF ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld", &i, &j);
            printf("Case %ld: %ld\n", kase, a[j] - a[i-1]);
        }
    }
    
    return 0;
}
