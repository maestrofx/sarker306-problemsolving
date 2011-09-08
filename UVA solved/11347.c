#include <stdio.h>
#include <ctype.h>
#include <math.h>
#define SIZE 1005

char sieve[SIZE];
int prime[1000], num;

int main(){
    long test, n, kase, k, i, m;
    unsigned long long x;
    int power[SIZE];
    char ch, flag;

    prime[num++] = 2;
    for( n = 4 ; n < SIZE ; n += 2 ) sieve[n] = 1;
    for( n = 3 ; n < SIZE ; n +=2 ){
        if( sieve[n] == 0 ){
            for( k = 2 * n ; k < SIZE ; k += n ) sieve[k] = 1;
            prime[num++] = n;
        }
    }

    while(scanf("%ld", &test) != EOF){
        getchar();
        for(kase = 1 ; kase <= test ; kase++ ){
            n = k = 0, x = 1;
            while((ch = getchar()) != '\n'){
                if( isdigit(ch) ) n = 10 * n + ch - '0';
                else if( ch == '!' ) k++;
            }

            printf("Case %ld: ", kase);
            /*printf("%ld %ld\n", n, k);*/
            for( i = 0 ; i < SIZE ; i++ ) power[i] = 0;
            for( ; n > 0 ; n -= k ){
                for( i = 0 ; i < num && prime[i] <= n ; i++ ){
                    m = n;
                    while( m % prime[i] == 0 ) power[prime[i]]++, m /= prime[i];
                }
            }

            for( i = flag = 0 ; i <= SIZE && !flag ; i++ ){
                if( log10(x) + log10( power[i] + 1 ) > 18 ) flag = 1;
                else x *= power[i] + 1 ;
            }

            if(flag || x> 1000000000000000000LL ) puts("Infinity");
            else printf("%lld\n", x);
        }
    }

    return 0;
}
