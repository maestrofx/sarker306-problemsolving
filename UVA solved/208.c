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

int adj[22][22], vis[22], deg[22], route[22], fw[22][22];
int dest;
long cntRoute;

void walk(int node, int ind){
	int i, v;
	
	vis[node]++;
	
	if ( node == dest ){
		printf("1");
		for ( i = 0 ; i < ind ; i++ ) printf(" %d", route[i]);
		puts("");
		cntRoute++;
	}
	else for ( i = 0 ; i < deg[node] ; i++ ){
		v = adj[node][i];
		if ( vis[v] == 0 && fw[v][dest] ){
			route[ind] = v;
			walk(v, ind + 1);
		}
	}
	
	vis[node]--;
}

void precalcReachability(){
	int i, j, k;
	
	for ( k = 1 ; k < 21 ; k++ )
		for ( i = 1 ; i < 21 ; i++ )
			for ( j = 1 ; j < 21 ; j++ )
				fw[i][j] |= (fw[i][k] & fw[k][j]);
}

void sortList(){
	int i, j, k;
	
	for ( k = 1 ; k < 21 ; k++ )
		for ( i = 0 ; i < deg[k] ; i++ )
			for ( j = i + 1 ; j < deg[k] ; j++ )
				if ( adj[k][i] > adj[k][j] ) adj[k][i] ^= adj[k][j] ^= adj[k][i] ^= adj[k][j];
}

int main(){
	int u, v, ks = 1;
	
	while ( scanf("%d", &dest) == 1 ){
		memset(deg, 0, sizeof(deg));
		memset(vis, 0, sizeof(vis));
		memset(fw, 0, sizeof(fw));
		
		while ( 1 ) {
			scanf("%d%d", &u, &v);
			if ( u == 0 && v == 0 ) break;
			adj[u][deg[u]++] = v;
			adj[v][deg[v]++] = u;
			fw[u][v] = fw[v][u] = 1;
		}
		
		precalcReachability();
		sortList();
		printf("CASE %d:\n", ks++);
		cntRoute = 0;
		walk(1, 0);
		printf("There are %ld routes from the firestation to streetcorner %d.\n", cntRoute, dest);
	}
	
	return 0;
}

