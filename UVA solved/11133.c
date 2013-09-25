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

ll dp[45][45];

void init(){
	int i, j, k;
	
	for ( i = 0 ; i <= 44 ; i++ )
		for ( j = i + 1 ; j <= 44 ; j++ )
			if ( j % ( j - i ) == 0 ){
				dp[i][j] = 1;
			}

	for ( k = 0 ; k <= 44 ; k++ )
		for ( i = 0 ; i <= 44 ; i++ )
			for ( j = 0 ; j <= 44 ; j++ )
				dp[i][j] += dp[i][k] * dp[k][j];
}

int main(){
	int st, en;
	
	init();
	while ( scanf("%d%d", &st, &en) == 2 ){
		if ( st >= en ) break;
		printf("%d %d %lld\n", st, en, dp[st][en]);
	}
	
	return 0;
}

