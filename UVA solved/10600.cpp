#include <cstdio>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())
#define SORT(x) sort(ALL(x))
#define mp make_pair
#define pb push_back
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

struct Edge{
	int u, v, cost;
};

struct Cmp{
	bool operator()(const Edge &p, const Edge &q){
		return p.cost < q.cost;
	}
};

Edge edges[1000005];
char valid[1000005];
int parent[1005], rank[1005];
vector<int>used;

void initSet(int n){
	for ( int i = 0 ; i <= n ; i++ ) parent[i] = i, rank[i] = 1;
}

int findSet(int x){
	if ( x != parent[x] ) parent[x] = findSet(parent[x]);
	return parent[x];
}

void link(int x, int y){
	if ( rank[x] > rank[y] ){
		parent[y] = x;
	}
	else{
		parent[x] = y;
		if ( rank[x] == rank[y] ) rank[y]++;
	}
}

int findMST(int n, int m, int flag){
	int e = 0, i, cost = 0;
	
	initSet(n);
	for ( i = 0 ; e != n-1 && i < m ; i++ ){
		if ( valid[i] == 0 ) continue;
		int parU = findSet(edges[i].u), parV = findSet(edges[i].v);
		if ( parU != parV ){
			link(parU, parV);
			if ( flag ) used.pb(i);
			cost += edges[i].cost;
			e++;
		}
	}
	
	if ( e != n - 1 ) return INT_MAX;
	return cost;
}

int main(){
	int test;
	int n, m;
	
	while ( scanf("%d", &test) == 1 ){
		for ( int kase = 1 ; kase <= test ; kase++ ){
			scanf("%d%d", &n, &m);
			for ( int i = 0 ; i < m ; i++ )
				scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].cost);

			sort(edges, edges + m, Cmp());
			for ( int i = 0 ; i < m ; i++ ) valid[i] = 1;
			
			int minCost = findMST(n, m, 1);
			int secCost = INT_MAX;
			
			for ( int i = 0 ; i < n - 1 ; i++ ){
				valid[used[i]] = 0;
				
				int tmp = findMST(n, m, 0);
				if ( tmp < secCost ) secCost = tmp;
				
				valid[used[i]] = 1;
			}
			
			printf("%d %d\n", minCost, secCost);
			used.clear();
		}
	}
	
	return 0;
}

