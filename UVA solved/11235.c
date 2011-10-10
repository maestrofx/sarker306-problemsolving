#include <stdio.h>
#include <math.h>
#define SIZE 100000
#define LOGSIZE 20

long A[SIZE+2];
long val[SIZE+2];
long M[SIZE+2][LOGSIZE+2];

unsigned long upperBound(long *arr, unsigned long n, long num ){
    unsigned long low = 0, high = n, mid;
    
    while ( low + 1 < high ) {
        mid = ( low + high ) >> 1;
        if ( arr[mid] > num ) high = mid;
        else low = mid;
    }
    
    return high;
}

void preprocess(long N){
     long i, j;
   
  /*initialize M for the intervals with length 1*/
      for (i = 0; i < N; i++)
          M[i][0] = i;
  /*compute values from smaller to bigger intervals*/
      for (j = 1; 1 << j <= N; j++)
          for (i = 0; i + (1 << j) - 1 < N; i++)
              if (A[M[i][j - 1]] >= A[M[i + (1 << (j - 1))][j - 1]])
                  M[i][j] = M[i][j - 1];
              else
                  M[i][j] = M[i + (1 << (j - 1))][j - 1];
}

long RMQ(long lo, long hi){ /* Range Maximum*/
    long k = log(hi - lo + 1)/log(2);
    
    if ( A[M[lo][k]] >= A[M[hi - ( 1<<k ) + 1][k]] ) return M[lo][k];
    else return M[hi - ( 1<<k ) + 1][k];
}

int main(){
    long n, q, i, lo, hi, x, y, a, b, c;
    
    while( scanf("%ld", &n)!= EOF){
        if ( n == 0 ) break;
        scanf("%ld", &q);
        for ( i = x = 0 ; i < n ; i++ ){
            scanf("%ld", val + i );
            y = val[i];
            if ( x == y ) A[i] = A[i-1] + 1;
            else A[i] = 1, x = y;
        }
        
        val[i] = SIZE + 10;
        /*for ( i = 0 ; i < n ; i++ ) printf("%ld ", A[i]);
        puts("");*/
        preprocess(n);
        while ( q-- ){
            a = b = c = -1;
            scanf("%ld%ld", &x, &y); /* index count from 0 to n-1*/
            x--, y--;
            if ( (y - x) == (A[y] - A[x]) ) printf("%ld\n", y - x + 1);
            else{
                lo = upperBound(val, n + 1, val[x]);
                hi = y - A[y];
                a = A[lo-1] - A[x] + 1;
                if ( lo <= hi ){
                    b = A[RMQ(lo, hi)];
                    /*printf("RMQ = %ld  ", b);*/
                }
                /*printf("low = %ld, high = %ld\n", lo, hi);*/
                c = A[y];
                if ( c < b ) c = b;
                if ( c < a ) c = a;
                printf("%ld\n", c);
            }
        }
    }
    
    return 0;
}
