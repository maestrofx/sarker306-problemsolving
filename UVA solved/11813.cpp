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
#include <stack>
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
#define SIZE 100001

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

struct Edge{
	long v;
	unsigned long dis;
	
	bool operator<(const Edge &p) const { return dis < p.dis; };
};

struct Cmp{
	bool operator()(const Edge& p, const Edge& q){
		return p.dis > q.dis;
	}
};

typedef Edge Pos;

list<Edge> adj[SIZE];
long n, e;
int d;
long venue[11];
unsigned long matrix[11][11];
unsigned long dist[SIZE];

void adjClear(){
	long i;
	
	for ( i = 0 ; i <= n ; i++ ) adj[i].clear();
}

void dijkstra(long src){
	long i;
	priority_queue<Pos, vector<Pos>, Cmp > pq;
	Pos st;
	
	st.v = src, st.dis = 0;
	pq.push(st);
	for ( i = 0 ; i <= n ; i++ ) dist[i] = ULONG_MAX;
	dist[src] = 0;
	
	while ( pq.empty() == false ){
		Pos u = pq.top();
		pq.pop();
		
		if ( u.dis != dist[u.v] ) continue;
		for ( list<Edge>::iterator ptr = adj[u.v].begin() ; adj[u.v].end() != ptr ; ptr++ ){
			if ( dist[ptr->v] > dist[u.v] + ptr->dis ){
				Pos v;
				dist[ptr->v] = dist[u.v] + ptr->dis;
				v.v = ptr->v, v.dis = dist[ptr->v];
				pq.push(v);
			}
		}
	}
}

unsigned long dp[11][1<<11];
int vis[11][1<<11], Turn;

unsigned long rec(int pos, unsigned mask){
	unsigned long res = ULONG_MAX, temp;
	int i;
	
	if ( pos == 0 && mask == ~(~0<<d) ) return 0;
	if ( vis[pos][mask] == Turn ) return dp[pos][mask];
	
	vis[pos][mask] = Turn;
	for ( i = 0 ; i < d ; i++ ){
		if ( i == pos ) continue;
		if ( i == 0 && (mask | 1) != ~(~0<<d)) continue;
		if ( mask & (1<<i) ) continue;
		temp = rec(i, mask | (1<<i)) + matrix[pos][i];
		if ( temp < res ) res = temp;
	}
	
	return dp[pos][mask] = res;
}

unsigned long findTotalDist(){
	int i, j;

	for ( i = 0 ; i < d ; i++ ){
		dijkstra(venue[i]);
		for ( j = 0 ; j < d ; j++ ) matrix[i][j] = dist[venue[j]];
	}

	Turn++;
	return rec(0, 0);
}

int main(){
	int test, i;
	long u, v, w;
	
	while ( scanf("%d", &test) == 1 ){
		while ( test-- ){
			scanf("%ld%ld", &n, &e);
			while ( e-- ){
				Pos p;
				scanf("%ld%ld%ld", &u, &v, &w);
				p.v = u, p.dis = w;
				adj[v].pb(p);
				p.v = v;
				adj[u].pb(p);
			}
			
			scanf("%d", &d);
			d++;
			for ( i = 1 ; i < d ; i++ ) scanf("%ld", venue + i);
			printf("%lu\n", findTotalDist());
			adjClear();
		}
		
		break;
	}
	
	return 0;
}

