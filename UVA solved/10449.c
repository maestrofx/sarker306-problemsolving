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

int adj[201][301], deg[201], vis[201];
long m;
int n, b[201];
long cost[201];

void relax(int u, int v){
	long w = b[v] - b[u];
	
	w = w * w * w;
	if ( cost[u] != LONG_MAX && cost[v] > cost[u] + w ) cost[v] = cost[u] + w;
}

void dfs(int u){
	int i;
	
	vis[u]++;
	cost[u] = LONG_MIN;
	for ( i = 0 ; i < deg[u] ; i++ )
		if ( vis[adj[u][i]] == 0 ) dfs(adj[u][i]);

	vis[u]++;
}

void bellmanFord(int src){
	int i, j, k;
	long w;
	
	for ( i = 1 ; i <= n ; i++ ) cost[i] = LONG_MAX, vis[i] = 0;
	cost[src] = 0;

	for ( i = 1 ; i < n ; i++ )
		for ( j = 1 ; j <=n ; j++ )
			for ( k = 0 ; k < deg[j] ; k++ )
				relax(j, adj[j][k]);

	for ( j = 1 ; j <= n ; j++ )
		for ( k = 0 ; k < deg[j] ; k++ ){
			w = ( b [ adj[j][k]] - b[j] );
			w *= w * w;
			if ( cost[adj[j][k]] > cost[j] + w && vis[adj[j][k]] == 0 ) dfs(adj[j][k]);
		}
}

int main(){
	int u, q, v, ks = 1;
	long i, j;
	
	while ( scanf("%d", &n) == 1 ){
		for ( i = 1 ; i <= n ; i++ ) deg[i] = 0;
		for ( i = 1 ; i <= n ; i++ ) scanf("%d", &b[i]);
		scanf("%ld", &m);
		for ( i = 0 ; i < m ; i++ ){
			scanf("%d%d", &u, &v);
			adj[u][deg[u]++] = v;
		}
		
		bellmanFord(1);
		scanf("%d", &q);
		printf("Set #%d\n", ks++);
		while ( q-- ){
			scanf("%d", &u);
			if ( cost[u] < 3 || cost[u] == LONG_MAX ) puts("?");
			else printf("%ld\n", cost[u]);
		}
	}
	
	return 0;
}

