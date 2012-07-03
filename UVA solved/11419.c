#include <stdio.h>
#include <string.h>
#define MAXVERTICES 2005
#define INF 1<<14
#define NIL 0

int pair[MAXVERTICES], degree[MAXVERTICES], adj[MAXVERTICES>>1][MAXVERTICES>>1];
int dist[MAXVERTICES], T[MAXVERTICES];

int dfsAugment(int u){
	int i, v;
	
	if ( u == NIL ) return 1;
	for ( i = 0 ; i < degree[u] ; i++ ){
		v = adj[u][i];
		if ( dist[pair[v]] == dist[u] + 1 )
			if ( dfsAugment(pair[v]) ){
				pair[u] = v;
				pair[v] = u;
				return 1;
			}
	}
	
	dist[u] = INF;
	return 0;
}

int queue[MAXVERTICES + 2], head, tail;
int rightEncountered[MAXVERTICES + 2], rightIndex;

int bfsAugment(int leftNodes){
	int i, u, v;
	
	rightIndex = head = tail = 0;
	dist[NIL] = INF;
	for ( i = 1 ; i <= leftNodes ; i++ )
		if ( pair[i] == NIL )
			queue[tail++] = i, dist[i] = 0;
		else dist[i] = INF;
		
	while ( head != tail ){
		u = queue[head++];
		
		for ( i = 0; i < degree[u] ; i++ ){
			v = adj[u][i];
			if ( dist[pair[v]] == INF ){
				rightEncountered[rightIndex++] = v;
				dist[pair[v]] = dist[u] + 1;
				queue[tail++] = pair[v];
			}
		}
	}
	
	return (dist[NIL] != INF);
}

void graphInit( int nodes ){
	int i;
	
	for ( i = 0 ; i < nodes ; i++ )
		pair[i] = NIL, degree[i] = 0;
}

void HopcroftKarp(int leftNodes, int rightNodes){
	int i, matching = 0;
	
	while ( bfsAugment(leftNodes) ){
		for ( i = 1 ; i <= leftNodes ; i++ )
			if ( pair[i] == NIL && dfsAugment( i ) ) matching++;
	}
	
	memset(T, 1, sizeof(T));
	printf("%d", matching);
	for ( i = 0 ; i < tail ; i++ ) T[queue[i]] = 0;
	for ( i = 0 ; i < rightIndex ; i++ ) T[rightEncountered[i]] = 0;
	for ( i = 1 ; i <= leftNodes ; i++ ) if ( T[i] ) printf(" r%d", i);
	for ( i = 1 ; i <= rightNodes ; i++ ) if ( !T[i + leftNodes] ) printf(" c%d", i);
	puts("");
}

int main(){
	int row, col, u, v;
	long k;
	
	while ( scanf("%d%d%ld", &row, &col, &k) != EOF ){
		if ( row == 0 && col == 0 && k == 0 ) break;
		graphInit(row + col + 1);
		while ( k-- ){
			scanf("%d%d", &u, &v);
			adj[u][degree[u]++] = row + v;
		}
		
		HopcroftKarp(row, col);
	}
	
	return 0;
}
