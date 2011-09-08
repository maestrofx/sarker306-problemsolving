#include <stdio.h>
#define SIZE 10005

long long coeff[SIZE];

int main(){
    long n, k, i;

    while( scanf("%ld%ld", &n, &k) != EOF ){
        if( n == k && k == -1 ) break;

        for( i = 0 ; i <= n ; i++ ) scanf("%lld", &coeff[i]);
        while( n >= k ) coeff[n - k] -= coeff[n--];

        if( n < 0 ) printf("0\n");
        else{
            for( ; n >= 0 && coeff[n] == 0 ; n-- );
            printf("%lld", coeff[0]);
            for( i = 1 ; i <= n ; i++ ) printf(" %lld", coeff[i]);
            puts("");
        }
    }

    return 0;
}
