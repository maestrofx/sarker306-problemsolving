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

double gophers[51][2], holes[51][2], distnc[51][51];

double Distnc(int gInd, int hInd){
	double delx = gophers[gInd][0] - holes[hInd][0];
	double dely = gophers[gInd][1] - holes[hInd][1];
	
	return delx*delx + dely*dely;
}

#define SIZE 1002
int cap[SIZE][SIZE], N, gopher, hole;
int src, snk;
int maxFlow();

void constructGraph(double cutOff){
	for ( int i = 0 ; i < N ; i++ )
		for ( int j = 0 ; j < N ; j++ ) cap[i][j] = 0;

	for ( int i = 1 ; i <= gopher ; i++ ) cap[src][i] = 1;
	for ( int i = 1 ; i <= hole ; i++ ) cap[i + gopher][snk] = 1;

	for ( int i = 1 ; i <= gopher ; i++ )
		for ( int j = 1 ; j <= hole ; j++ )
			if ( distnc[i][j] < cutOff ) cap[i][j + gopher] = 1;
}

double bSearch(int k){
	double lo = 0, hi = 1e10;
	
	while ( fabs(lo - hi) > 1e-8 ){
		double mid = ( lo + hi ) / 2.0;
		constructGraph(mid);
		if ( maxFlow() >= gopher - k ) hi = mid;
		else lo = mid;
	}
	
	return sqrt(lo);
}

int main(){
	int test, ks, k;
	ios::sync_with_stdio(true);

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d%d", &gopher, &hole, &k);

			for ( int i = 1 ; i <= gopher ; i++ ) scanf("%lf%lf", &gophers[i][0], &gophers[i][1]);
			for ( int i = 1 ; i <= hole ; i++ ) scanf("%lf%lf", &holes[i][0], &holes[i][1]);
			
			for ( int i = 1 ; i <= gopher ; i++ )
				for ( int j = 1 ; j <= hole ; j++ ) distnc[i][j] = Distnc(i, j);
				
			src = 0, snk = gopher + hole + 1;
			N = snk + 1;

			printf("Case #%d:\n", ks);
			if ( gopher == 0 || gopher == k ) puts("0.000\n");
			else if ( gopher - k > hole ) puts("Too bad.\n");
			else printf("%.3lf\n\n", bSearch(k));
		}
	}

	return 0;
}

int now[SIZE], parent[SIZE], L[SIZE], minCap[SIZE];
int q[SIZE];

bool bfs(){
	int head, tail;

	head = tail = 0;
	for ( int i = 0 ; i < N ; i++ ) parent[i] = -1, L[i] = -1, minCap[i] = INT_MAX;
	L[src] = 0;

	q[tail++] = src;
	while ( head != tail ){
		int u = q[head++];
		if ( u == snk ) return true;
		for ( int i = 0 ; i < N ; i++ ){
			if ( cap[u][i] > 0 && L[i] == -1 ){
				parent[i] = u;
				L[i] = L[u] + 1;
				minCap[i] = min(cap[u][i], minCap[u]);
				q[tail++] = i;
			}
		}
	}

	return false;
}

int dfs(int u, int fl){
	if ( u == snk ) return fl;

	for ( int &i = now[u] ; i < N ; i++ ){
		if ( cap[u][i] > 0 && L[i] == L[u] + 1 ){
			int df = dfs(i, min(cap[u][i], fl));
			if ( df > 0 ){
				cap[u][i] -= df;
				cap[i][u] += df;
				return df;
			}
		}
	}

	return 0;
}

int maxFlow(){
	int totFlow = 0;

	while ( bfs() ){
		for ( int i = 0 ; i < N ; i++ ) now[i] = 0;
		while ( true ){
			int df = dfs(src, INT_MAX);
			if ( df > 0 ) totFlow += df;
			else break;
		}
	}

	return totFlow;
}

