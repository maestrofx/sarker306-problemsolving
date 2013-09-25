#include <stdio.h>
#include <string.h>

int k;

void matrixMultiply(long long to[][30], long long fir[][30], long long sec[][30], long long mod){
    int i, j, l;
    long long sum;
    
    for ( i = 0 ; i <= k ; i++ )
        for ( j = 0 ; j <= k ; j++ ){
            sum = 0;
            for ( l = 0 ; l <= k ; l++ )
                sum = ( sum + fir[i][l] * sec[l][j] ) % mod;
            
            to[i][j] = sum;
        }
}

void BigModMatrix( long long to[][30], long long from[][30], long long power, long long mod ){
    long long tmp[30][30];
    int i, j;
    
    
    if ( power <= 0 ) {
        for ( i = 0 ; i <= k ; i++ )
            for ( j = 0 ; j <= k ; j++ )
                to[i][j] = 0;
                
        for ( i = 0 ; i <= k ; i++ )
            to[i][i] = 1;
        
        return;
    }
    
    BigModMatrix(tmp, from, power>>1, mod);
    
    matrixMultiply(to, tmp, tmp, mod);
    if ( (power & 01) ){
        for ( i = 0 ; i <= k ; i++ )
            for ( j = 0 ; j <= k ; j++ )
                tmp[i][j] = to[i][j];
        matrixMultiply(to, tmp, from, mod);
    }
}

int main(){
    int test, kase, i, j;
    long long m, n, arr[30][30], res[30][30], inp[30];
    long long sum;
    
    while ( scanf("%d", &test) == 1 ){
        for ( kase = 1 ; kase <= test ; kase++ ){
            if ( kase > 1 ) puts("");
            
            for ( i = 0 ; i <= k ; i++ )
                for ( j = 0 ; j <= k ; j++ )
                    arr[i][j] = 0;
                    
            scanf("%d%lld%lld", &k, &m, &n);
            arr[k][k] = 1;
            for ( i = 0 ; i <= k ; i++ ){
                scanf("%lld", &arr[0][i]);
                if ( arr[0][i] < 0 ) arr[0][i] = ( m - (-arr[0][i]) % m );
                arr[0][i] %= m;
            }
            
            for ( i = 1 ; i < k ; i++ ) arr[i][i-1] = 1;
            for ( i = k - 1 ; i >= 0 ; i-- ){
                scanf("%lld", inp + i);
                if ( inp[i] < 0 ) inp[i] = ( m - (-inp[i]) % m );
                inp[i] %= m;
            }
            
            inp[k] = 1;
            
            if ( k == 0 ){
                inp[0] = arr[0][0]%m;
                printf("%lld\n", inp[0]);
            }
            else if ( n < k ) printf("%lld\n", inp[k-n-1]%m);
            else{
                BigModMatrix( res, arr, n - k + 1, m );
                for ( sum = 0, i = 0 ; i <= k ; i++ )
                    sum = ( sum + res[0][i] * inp[i])%m;
                
                printf("%lld\n", sum);
            }
        }
    }
    
    return 0;
}
