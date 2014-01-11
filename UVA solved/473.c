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

int dp[1000][120][120];
int len[1000], n, t, m;
int vis[1000][120][120], ks = 1;

int rec(int pos, int time, int remDsk){
	int res = 0, temp = 0;
	
	if ( pos == n ) return 0;
	if ( vis[pos][time][remDsk] == ks ) return dp[pos][time][remDsk];
	
	vis[pos][time][remDsk] = ks;
	if ( time + len[pos] <= t ) res = 1 + rec(pos + 1, time + len[pos], remDsk);
	else if ( remDsk && len[pos] <= t ) temp = 1 + rec(pos + 1, len[pos], remDsk - 1);
	if ( res < temp ) res = temp;
	temp = rec(pos + 1, time, remDsk);
	if ( res < temp ) res = temp;
	
	return dp[pos][time][remDsk] = res;
}

int iter(int pos, int time, int remDsk){
	int i, j, k;
	
	for ( j = 0 ; j <= t ; j++ )
		for ( k = 0 ; k <= remDsk ; k++ )
			dp[n][j][k] = 0;

	for ( i = n - 1 ; i >= 0 ; i-- ){
		for ( j = t ; j >= 0 ; j-- ){
			for ( k = 0 ; k <= remDsk ; k++ ){
				dp[i][j][k] = 0;
				if ( len[i] + j <= t ) dp[i][j][k] = 1 + dp[i+1][len[i]+j][k];
				if ( k && len[i] <= t ) dp[i][j][k] = MAX(dp[i][j][k], dp[i+1][len[i]][k-1] + 1);
				dp[i][j][k] = MAX(dp[i][j][k], dp[i+1][j][k]);
			}
		}
	}
	
	return dp[0][0][remDsk];
}

int main(){
	int test, i;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d%d", &n, &t, &m);
			for ( i = 0 ; i < n - 1 ; i++ ) scanf("%d,", &len[i]);
			scanf("%d", &len[n-1]);
			if ( ks > 1 ) puts("");
			printf("%d\n", iter(0, 0, m - 1));
		}
	}
	
	return 0;
}
/*
2
10 5 3
3, 5, 1, 2, 3, 5, 4, 1, 1, 5
1 1 1
1
*/
