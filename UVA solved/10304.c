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

typedef unsigned long long llu;
typedef long long ll;

int n;
long freq[251];
int root[251][251];
long cost[251][251];

int main(){
	int i, j, k, len;
	
	while ( scanf("%d", &n) == 1 ){
		for ( i = 1 ; i <= n ; i++ ){
			scanf("%ld", &freq[i]);
			freq[i] += freq[i-1];
		}
		
		for ( i = 1 ; i <= n ; i++ ) root[i][i] = i, cost[i][i] = 0, cost[i][i-1] = 0, root[i][i-1] = i;
		
		for ( len = 2 ; len <= n ; len++ ){
			for ( i = 1 ; i + len - 1 <= n ; i++ ){
				j = i + len - 1;
				cost[i][j] = LONG_MAX;
				for ( k = root[i][j-1] ; k <= root[i+1][j] ; k++ ){
					if ( cost[i][j] > cost[i][k - 1] + cost[k + 1][j] - freq[i-1] + freq[j] - freq[k] + freq[k-1] ){
						cost[i][j] = cost[i][k - 1] + cost[k + 1][j] - freq[i-1] + freq[j] - freq[k] + freq[k-1];
						root[i][j] = k;
					}
				}
			}
		}
		
		printf("%ld\n", cost[1][n]);
	}
	
	return 0;
}

