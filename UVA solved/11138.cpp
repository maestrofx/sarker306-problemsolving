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

#define SIZE 1002
int cap[SIZE][SIZE], N, blt, nts;
int src, snk;
int maxFlow();

int main(){
	int test, ks;
	ios::sync_with_stdio(true);
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &blt, &nts);
			src = 0, snk = blt + nts + 1;
			N = snk + 1;
			for ( int i = 0 ; i < N ; i++ )
				for ( int j = 0 ; j < N  ; j++ ) cap[i][j] = 0;

			for ( int i = 1 ; i <= blt ; i++ )
				for ( int j = 1 ; j <= nts ; j++ )
					scanf("%d", &cap[i][j + blt]);

			for ( int i = 1 ; i <= blt ; i++ ) cap[src][i] = 1;
			for ( int i = 1 ; i <= nts ; i++ ) cap[i + blt][snk] = 1;
			
			printf("Case %d: a maximum of %d nuts and bolts can be fitted together\n", ks, maxFlow());
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

