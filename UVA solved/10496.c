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

int ks, INF = 20000;
int vis[11][1<<11], dp[11][1<<11];
int pts[11][2], n;

int manhattan(int a, int b){
	int delx = pts[a][0] - pts[b][0], dely = pts[a][1] - pts[b][1];
	if ( delx < 0 ) delx = -delx;
	if ( dely < 0 ) dely = -dely;
	return delx + dely;
}

int rec(int pos, unsigned mask){
	int res = INF, temp, i;
	
	if ( vis[pos][mask] == ks ) return dp[pos][mask];
	vis[pos][mask] = ks;
	
	for ( i = 0 ; i < n ; i++ ){
		if ( mask & (1<<i) ) continue;
		if ( i == pos ) continue;
		temp = rec(i, mask | (1<<i)) + manhattan(pos, i);
		if ( res > temp ) res = temp;
	}
	
	if ( res == INF && pos == 0 && mask == ~(~0u<<n) ) res = 0;
	return dp[pos][mask] = res;
}

int main(){
	int test, res, temp, i;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &n);
			scanf("%d%d", &pts[10][0], &pts[10][1]);
			scanf("%d", &n);
			for ( i = 0 ; i < n ; i++ ) scanf("%d%d", &pts[i][0], &pts[i][1]);
			pts[n][0] = pts[10][0], pts[n][1] = pts[10][1];
			n++;
			printf("The shortest path has length %d\n", rec(0,0));
		}
	}
	
	return 0;
}

