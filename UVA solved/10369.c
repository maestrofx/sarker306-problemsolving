#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXOUTPOSTS 501

typedef struct{
	int u, v;
	long long distance;
}edge;
edge Edges[MAXOUTPOSTS * MAXOUTPOSTS];
int coOrds[MAXOUTPOSTS][2], rank[MAXOUTPOSTS], parent[MAXOUTPOSTS];
long egCount;

void initOutposts(int N){
	int i;
	
	for( i = 0 ; i < N ; i++ ) parent[i] = i, rank[i] = 0;
}

long long sqrDistance(int x, int y){
	long long del1 = coOrds[x][0] - coOrds[y][0], del2 = coOrds[x][1] - coOrds[y][1];
	
	return del1*del1 + del2*del2;
}

int cmpDistance( const void *a, const void *b ){
	edge *x = (edge*)a, *y = (edge*)b;
	
	return ( x->distance > y->distance ) ? 1 : -1;
}

int findParent(int x){
    if ( x != parent[x] ) parent[x] = findParent(parent[x]);
    return parent[x];
}

void link(int x,int y){
    if ( rank[x] > rank[y] ) parent[y] = x;
    else{
		if( rank[x] == rank[y] ) rank[y]++;
		parent[x] = y;
    }
}

double minimumDistanceReceiver(int op, int stl){
	int mstEdges = 0, parU, parV;
	long i;
	long long last = 0;
	
	initOutposts(op);
	qsort(Edges, egCount, sizeof(edge), cmpDistance);
	
	for ( i = 0 ; i < egCount && ( mstEdges + stl ) < op ; i++ ){
		parU = findParent(Edges[i].u);
		parV = findParent(Edges[i].v);
		/*printf("%d %d %lld   %d %d\n", Edges[i].u, Edges[i].v, Edges[i].distance,
			parU, parV);*/
		
		if ( parU != parV ){
			link( parU, parV );
			mstEdges++;
			/*printf("inced\n");*/
			last = Edges[i].distance;
		}
	}
	
	return sqrt( last );
}

int main(){
	int testCases, satellites, outposts;
	long i, j;
	
	scanf("%d", &testCases);
	while ( testCases-- ){
		scanf("%d%d", &satellites, &outposts);
		for ( i = 0 ; i < outposts ; i++ )
			scanf("%d%d", &coOrds[i][0], &coOrds[i][1]);
		
		egCount = 0;
		for ( i = 0 ; i < outposts ; i++ )
			for ( j = i + 1 ; j < outposts ; j++ ){
				Edges[egCount].u = i, Edges[egCount].v = j;
				Edges[egCount++].distance = sqrDistance(i, j);
			}
			
		printf("%.2lf\n", minimumDistanceReceiver(outposts, satellites));
	}
	
	return 0;
}
