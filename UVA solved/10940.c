#include <stdio.h>
#define SIZE 5000002
long arr[SIZE], arr1[SIZE];

long calc1(long);
long calc(long n){
     if ( arr[n] ) return arr[n];
     return arr[n] = n&1 ? 2*calc1(n/2) : 2*calc(n/2);
}

long calc1(long n){
     if ( arr1[n] ) return arr1[n];
     return arr1[n] = n&1 ? ( 2*calc((n+1)/2) -1 )
        : ( 2*calc1((n+1)/2) -1 );
}

int main(){
    long n;
    
    arr[1] = 1, arr[2]=2;
    arr1[1] = 1, arr1[2] = 1;
    while ( scanf("%ld", &n) != EOF && n>0 ) printf("%ld\n", calc(n));
    return 0;
}
