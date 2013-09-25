#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef long long ll;
typedef unsigned long long llu;

int n, k;
int dist[601];

int tryWithMaxDist(int mxDist){
	int rem = k - 1, sum = 0, i;
	
	for ( i = 0 ; i < n ; i++ ){
		if ( sum + dist[i] > mxDist ){
			rem--;
			sum = dist[i];
		} else sum += dist[i];
	}
	
	return rem;
}

int search(){
	int lo = 0, hi = 1, i, mid = 0;
	
	for ( i = 0 ; i < n ; i++ ){
		hi += dist[i];
		if ( lo < dist[i] ) lo = dist[i];
	}
	
	if ( k >= n ) return lo;
	
	while ( lo + 1 < hi ){
		mid = ( lo + hi ) >> 1;
		if ( tryWithMaxDist(mid) >= 0 ) hi = mid;
		else lo = mid;
	}
	
	return lo + 1;
}

int main(){
	int i;
	
	while ( scanf("%d%d", &n, &k) == 2 ){
		k++, n++;
		for ( i = 0 ; i < n ; i++ ) scanf("%d", &dist[i]);
		printf("%d\n", search());
	}
	
	return 0;
}

