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

int cut[55], len, n;
long arr[55][55];
int root[55][55];

int main(){
	int i, j, k, l;
	cut[0] = 0;
	
	while ( scanf("%d", &len) == 1 && len > 0 ){
		scanf("%d", &n);
		cut[n + 1] = len;
		for ( i = 1 ; i <= n ; i++ ) scanf("%d", &cut[i]);
		
		for ( i = 0 ; i <= n ; i++ ) arr[i][i] = 0, arr[i][i+1] = 0, root[i][i] = i, root[i][i+1] = i+1;
		arr[n+1][n+1] = 0;
		
		n += 2;
		for ( l = 3 ; l <= n ; l++ ){
			for ( i = 0 ; i < n ; i++ ){
				j = i + l - 1;
				if ( j >= n ) break;
				arr[i][j] = LONG_MAX;
				for ( k = root[i][j-1] ; k <= root[i+1][j] ; k++ ){
					if ( arr[i][j] > arr[i][k] + arr[k][j] + cut[j] - cut[i] ){
						arr[i][j] = arr[i][k] + arr[k][j] + cut[j] - cut[i];
						root[i][j] = k;
					}
				}
			}
		}
		
		printf("The minimum cutting is %ld.\n", arr[0][n-1]);
	}
	
	return 0;
}

