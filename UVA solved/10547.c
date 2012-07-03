#include <stdio.h>

unsigned long long BigMod( unsigned long long base, unsigned long long power, unsigned long long mod ){
    unsigned long long temp;
    
    if ( power == 0 ) return 1;
    temp = BigMod( base, power >> 1 , mod );
    temp  = ( temp * temp ) % mod;
    return (power & 1) ? ( base *  temp )%mod : temp;
}

int main(){
    unsigned long long n, k;
    unsigned long long modValue[11];
    int i, t, kase = 1;
    for ( modValue[0] = 1, i = 1 ; i < 11 ; i++ ) modValue[i] = 10 * modValue[i-1];
    
    while ( scanf("%llu%llu%d", &k, &n, &t) == 3 ){
        if ( n == 0 && k == 0 && t == 0 ) break;
        printf("Case #%d: %llu\n", kase++, BigMod(k%modValue[t], n, modValue[t]));
    }
    
    return 0;
}
