#include <stdio.h>
#include <string.h>

long long arr[225][12][225];
int visited[225][12][225];
int now;

long long calculate( int resNumber, int resBucket, int last ){
    if ( resBucket == 0 ) return last==0;
    if ( last == resNumber && resBucket == 1 ) return 1;
    if ( resNumber < last || resNumber < resBucket ) return 0;
    if ( visited[resNumber][resBucket][last] == now )
        return arr[resNumber][resBucket][last];
    
    visited[resNumber][resBucket][last] = now;
    return arr[resNumber][resBucket][last] = calculate( resNumber - last, resBucket - 1, last )
        + calculate ( resNumber, resBucket, last + 1 );
}

void printKthSoln( int resNumber, int resBucket, int last, long long k ){
    long long temp;
    
    if ( resNumber == last ){
        printf("%d\n", last);
        return;
    }
    if ( resNumber < last || 0 > resBucket ) return;
    temp = calculate ( resNumber - last, resBucket - 1, last );
    if ( temp < k ) printKthSoln ( resNumber, resBucket, last + 1, k - temp );
    else{
        printf("%d\n", last);
        printKthSoln( resNumber - last, resBucket - 1, last, k );
    }
}

int main(){
    int n, m, test;
    long long k;
    
    scanf("%d", &test);
    while ( test-- ){
        now++;
        scanf("%d%d%d", &m, &n, &k);
        printKthSoln(m, n, 1, k);
    }
    
    return 0;
}
