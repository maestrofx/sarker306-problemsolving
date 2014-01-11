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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

// the maximum number of vertices + 1
#define NN 105

// adjacency matrix (fill this up)
ll cap[NN][NN];

// cost per unit of flow matrix (fill this up)
ll cost[NN][NN];

// flow network and adjacency list
ll fnet[NN][NN];
int adj[NN][NN], deg[NN];

// Dijkstra's successor and depth
int par[NN];        // par[source] = source;
ll d[NN];

// Labelling function
ll pi[NN];

#define CLR(a, x) memset( a, x, sizeof( a ) )
#define Inf (LLONG_MAX>>2)

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])
bool dijkstra( int n, int s, int t )
{
    for( int i = 0; i < n; i++ ) d[i] = Inf, par[i] = -1;
    d[s] = 0;
    par[s] = -n - 1;

    while( 1 )
    {
        // find u with smallest d[u]
        int u = -1;
		ll bestD = Inf;
        for( int i = 0; i < n; i++ ) if( par[i] < 0 && d[i] < bestD )
            bestD = d[u = i];
        if( bestD == Inf ) break;

        // relax edge (u,i) or (i,u) for all i;
        par[u] = -par[u] - 1;
        for( int i = 0; i < deg[u]; i++ )
        {
            // try undoing edge v->u
            int v = adj[u][i];
            if( par[v] >= 0 ) continue;
            if( fnet[v][u] && d[v] > Pot(u,v) - cost[v][u] )
                d[v] = Pot( u, v ) - cost[v][u], par[v] = -u-1;

            // try edge u->v
            if( fnet[u][v] < cap[u][v] && d[v] > Pot(u,v) + cost[u][v] )
                d[v] = Pot(u,v) + cost[u][v], par[v] = -u - 1;
        }
    }

    for( int i = 0; i < n; i++ ) if( pi[i] < Inf ) pi[i] += d[i];

    return par[t] >= 0;
}
#undef Pot

ll D;

ll mcmf3( int n, int s, int t, ll &fcost )
{
    // build the adjacency list
    CLR( deg, 0 );
    for( int i = 0; i < n; i++ )
    for( int j = 0; j < n; j++ )
        if( cap[i][j] || cap[j][i] ) adj[i][deg[i]++] = j;

    CLR( fnet, 0 );
    CLR( pi, 0 );
    ll flow = fcost = 0;

    // repeatedly, find a cheapest path from s to t
    while( dijkstra( n, s, t ) )
    {
        // get the bottleneck capacity
        ll bot = LLONG_MAX;
        for( int v = t, u = par[v]; v != s; u = par[v = u] ){
            ll tmp = fnet[v][u] ? fnet[v][u] : ( cap[u][v] - fnet[u][v] );
            if ( bot > tmp ) bot = tmp;
        }

        // update the flow network
        for( int v = t, u = par[v]; v != s; u = par[v = u] )
            if( fnet[v][u] ) { fnet[v][u] -= bot; fcost -= bot * cost[v][u]; }
            else { fnet[u][v] += bot; fcost += bot * cost[u][v]; }

        flow += bot;
    }

    return flow;
}

int main(){
	int n, m;
	int edges[5001][3];
	ll fcost, fflow, K;
	
	while ( scanf("%d%d", &n, &m) == 2 ){
		memset(cap, 0, sizeof(cap));
		for ( int i = 0 ; i <= n ; i++ )
			for ( int j = 0 ; j <= n  ; j++ ) cost[i][j] = Inf;
			
		for ( int i = 0 ; i < m ; i++ )
			for ( int j = 0 ; j < 3 ; j++ ) scanf("%d", &edges[i][j]);

		scanf("%lld%lld", &D, &K);
		cap[0][1] = cap[1][0] = D;
		cost[0][1] = cost[1][0] = 0;
		for ( int i = 0 ; i < m ; i++ ){
			int u = edges[i][0];
			int v = edges[i][1];
			int w = edges[i][2];
			
			cap[u][v] = cap[v][u] = K;
			cost[u][v] = cost[v][u] = w;
		}
		
		if ( D <= ( fflow = mcmf3(n + 1, 0, n, fcost) ) ) printf("%lld\n", fcost);
		else printf("Impossible.\n");
		//printf("%lld\n", fflow);
	}
	
	return 0;
}

