#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

char grid[101][101];
int comp[101][101], compSz;
int vis[101][101], ks = 1;
int xdir[] = {-1,-1,-1,0,0,1,1,1};
int ydir[] = {-1,0,1,-1,1,-1,0,1};
int vdir[] = {-1, 0, 1};
int R, C;

void dfs(int x, int y, int cId){
	vis[x][y] = ks;
	comp[x][y] = cId;
	
	for ( int i = 0 ; i < 8 ; i++ ){
		int u = x + xdir[i];
		int v = y + ydir[i];
		if ( u >= 0 && u < R && v >= 0 && v < C ){
			if ( grid[u][v] == '#' && vis[u][v] != ks ) dfs(u, v, cId);
		}
	}
}

struct Edge{
	int u, v, w;
	Edge(int _u, int _v, int _w){
		u = _u, v = _v, w = _w;
	}
};

vector<Edge>edgs;
vector<int>Rank;
vector<int>Parent;

bool Cmpr(const Edge &a, const Edge &b){
	return a.w < b.w;
}

int findSet(int x){
	if ( x != Parent[x] ) Parent[x] = findSet(Parent[x]);
	return Parent[x];
}

void link(int x, int y){
	if ( Rank[x] > Rank[y] ){
		Parent[y] = x;
	}
	else{
		Parent[x] = y;
		if ( Rank[x] == Rank[y] ) Rank[y]++;
	}
}

void initTree(){
	int cost = 0, now = 0, forest = 0;
	compSz = 0;
	
	edgs.clear();
	memset(comp, -1, sizeof(comp));
	for ( int i = 0 ; i < R ; i++ ){
		for ( int j = 0 ; j < C ; j++ ){
			if ( grid[i][j] == '#' && vis[i][j] != ks ){
				dfs(i, j, ++compSz);
			}
		}
	}

	Rank.resize(compSz + 1);
	Parent.resize(compSz + 1);

	for ( int i = 0 ; i <= compSz ; i++ ) Rank[i] = 1, Parent[i] = i;
	
	for ( int i = 0 ; i < R ; i++ ){
		for ( int j = 0 ; j < C ; j++ ){
			if ( grid[i][j] == '#' ){
				for ( int k = 1 ; k <= R ; k++ ){
					int u = i + k;
					if ( u >= R ) break;
					for ( int l = 0 ; l < 3 ; l++ ){
						int v = j + vdir[l];
						if ( v < 0 || v >= C ) continue;
						if ( comp[u][v] >= 0 && comp[u][v] != comp[i][j] ){
							edgs.push_back(Edge(comp[i][j], comp[u][v], k-1));
							edgs.push_back(Edge(comp[u][v], comp[i][j], k-1));
						}
					}
				}
				
				for ( int k = 1 ; k <= C ; k++ ){
					int v = j + k;
					if ( v >= C ) break;
					for ( int l = 0 ; l < 3 ; l++ ){
						int u = i + vdir[l];
						if ( u < 0 || u >= R ) continue;
						if ( comp[u][v] >= 0 && comp[u][v] != comp[i][j] ){
							edgs.push_back(Edge(comp[i][j], comp[u][v], k-1));
							edgs.push_back(Edge(comp[u][v], comp[i][j], k-1));
						}
					}
				}
			}
		}
	}
	
	sort(edgs.begin(), edgs.end(), Cmpr);
	
	for ( int i = 0 ; i < edgs.size() ; i++ ){
		Edge cur = edgs[i];
		int parU = findSet(edgs[i].u), parV = findSet(edgs[i].v);
		if ( parU != parV ){
			link(parU, parV);
			cost += edgs[i].w;
			now++;
		}
		//printf("%d %d %d\n", cur.u, cur.v, cur.w);
	}
	
	for ( int i = 1 ; i <= compSz ; i++ ){
		if (Parent[i] == i) forest++;
	}
	
	if ( cost == 0 ){
		if ( compSz <= 1 ) puts("No bridges are needed.");
		else puts("No bridges are possible.");
	}
	else{
		printf("%d bridge", now);
		if ( now > 1 ) putchar('s');
		printf(" of total length %d\n", cost);
	}
	if ( forest >= 2 )printf("%d disconnected groups\n", forest);
}

int main(){
	while ( scanf("%d%d", &R, &C) != EOF ){
		if ( R == 0 && C == 0 ) break;
		for ( int i = 0 ; i < R ; i++ ) scanf("%s", grid[i]);
		
		if ( ks > 1 ) puts("");
		printf("City %d\n", ks);
		initTree();
		ks++;
	}
	
	return 0;
}

