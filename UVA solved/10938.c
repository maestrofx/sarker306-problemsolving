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

#define SIZE 5005
#define LGSZ 14

int parent[SIZE], L[SIZE];
int P[SIZE][LGSZ];

int N;
int adj[SIZE][SIZE];
int deg[SIZE];

void initTree(){
	int i;
	
	for ( i = 1 ; i <= N ; i++ ) deg[i] = 0, parent[i] = -1, L[i] = -1;
	L[1] = 0;
	parent[1] = 1;
}

void dfs(int u){
	int i, v;
	
	for ( i = 0 ; i < deg[u] ; i++ ){
		v = adj[u][i];
		if ( parent[v] == -1 ){
			parent[v] = u;
			L[v] = L[u] + 1;
			dfs(v);
		}
	}
}

void initTable(){
	int i, j;
	
	dfs(1);
	
	for (i = 1; i <= N; i++)
          for (j = 0; (1 << j) <= N; j++)
              P[i][j] = -1;

	for ( i = 1 ; i <= N ; i++ ) P[i][0] = parent[i];
	
	for ( j = 1 ; (1<<j) <= N ; j++ )
		for ( i = 1 ; i <= N ; i++ )
			if ( P[i][j-1] != -1 )
				P[i][j] = P[P[i][j-1]][j-1];
}

int findLCA(int p, int q){
	int i, j, lg;
	
	if ( L[p] < L[q] ) p ^= q ^= p ^= q;
	for ( lg = 0 ; (1<<lg) <= L[p] ; lg++);
	lg--;
	for ( i = lg ; i >= 0 ; i-- )
		if ( L[p] - (1<<i) >= L[q] ) p = P[p][i];

	if ( p == q ) return p;
	
	for ( i = lg ; i >= 0 ; i-- )
		while ( P[p][i] != -1 && P[p][i] != P[q][i] )
			p = P[p][i], q = P[q][i];
	
	return parent[p];
}

int findKthAncestor(int u, int K){
	int i, lg;
	
	for ( lg = 0 ; (1<<lg) <= K ; lg++ );
	lg--;
	
	for ( i = lg ; i >= 0 ; i-- ){
		if ( K & (1<<i) ) u = P[u][i];
	}
	
	return u;
}

int main(){
	int i, u, v, q, w, dist;
	
	while ( scanf("%d", &N) == 1 && N > 0 ){
		initTree();
		
		for ( i = 1 ; i < N ; i++ ){
			scanf("%d%d", &u, &v);
			adj[u][deg[u]++] = v;
			adj[v][deg[v]++] = u;
		}
		
		initTable();
		scanf("%d", &q);
		while ( q-- ){
			scanf("%d%d", &u, &v);
			if ( L[u] < L[v] ) u ^= v ^= u ^= v;
			
			w = findLCA(u, v);
			dist = L[u] + L[v] - 2 * L[w];

			if ( w == v ){
				/*printf("Case 1: In %d's side totally\n", u);*/
				w = findKthAncestor(u, dist/2);
			}
			else if ( L[u] == L[v] ){
				/*printf("Case 3: Same level\n");*/
			}
			
			else{
				/*printf("Case 2 : %d[%d] > %d[%d]\n", u, L[u], v, L[v]);*/
				w = findKthAncestor(u, dist/2);
			}

			/*printf("%d\n", dist);
			printf("%d\n", w);*/
			if ( dist & 1 ){
				u = w;
				v = parent[w];
				if ( u > v ) u ^= v ^= u ^= v;
				printf("The fleas jump forever between %d and %d.\n", u, v);
			}
			else printf("The fleas meet at %d.\n", w);
		}
	}
	
	return 0;
}

