#include <stdio.h>

unsigned lowerBound(unsigned long *arr, unsigned n, unsigned long num ){
    unsigned low = 0, high = n, mid;
    
    while ( low + 1 < high ) {
        mid = ( low + high ) >> 1;
        if ( arr[mid] >= num ) high = mid;
        else low = mid;
    }
    
    return low;
}

unsigned upperBound(unsigned long *arr, unsigned n, unsigned long num ){
    unsigned low = 0, high = n, mid;
    
    while ( low + 1 < high ) {
        mid = ( low + high ) >> 1;
        if ( arr[mid] > num ) high = mid;
        else low = mid;
    }
    
    return high;
}

int main(){
    unsigned n, i, ind;
    unsigned long arr[50005], m;
    
    arr[0] = 0;
    while ( scanf("%u", &n) != EOF ) {
        for ( i = 1 ; i <= n ; i++ ) scanf("%lu", arr + i );
        arr[i] = 1<<31 ;
        scanf("%u", &i);
        n++;
        while ( i-- ) {
            scanf("%lu", &m);
            ind = lowerBound(arr, n, m);
            ind ? printf("%ld", arr[ind]) : putchar('X');
            ind = upperBound(arr, n, m);
            ( ind != n ) ? printf(" %ld\n", arr[ind]) : puts(" X");
        }
    }
    
    return 0;
}
