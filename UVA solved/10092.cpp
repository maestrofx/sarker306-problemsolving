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

#define SIZE 1022
int nP, nK;
int N, src = 0, snk;
int maxFlow();
void printAssignment();
int flow[SIZE][SIZE], cap[SIZE][SIZE];

int main(){
	ios::sync_with_stdio(true);
	while ( scanf("%d%d", &nK, &nP) == 2 ){
		if ( nP == 0 && nK == 0 ) break;
		N = nP + nK + 2;
		snk = N - 1;
		memset(cap, 0, sizeof(cap));
		memset(flow, 0, sizeof(flow));
		
		for ( int i = 1 ; i <= nK ; i++ ){
			scanf("%d", &cap[0][i]);
		}
		
		for ( int i = 1 ; i <= nP ; i++ ){
			int deg;
			scanf("%d", &deg);
			while ( deg-- ){
				int category;
				scanf("%d", &category);
				cap[category][i + nK]++;
			}
			
			cap[i + nK][snk] = 1;
		}
		
		maxFlow();
		printAssignment();
	}
	
	return 0;
}

bool bfs();
int dfs(int, int);
int parent[SIZE], minCap[SIZE];

void printAssignment(){
	int flag = 1;
	
	for ( int i = 1 ; i <= nK ; i++ ){
		if ( cap[src][i] != 0 ){
			flag = 0;
			break;
		}
	}
	
	printf("%d\n", flag);
	if ( flag == 0 ) return;
	for ( int i = 1 ; i <= nK ; i++ ){
		flag = 0;
		for ( int j = nK + 1 ; j <= nK + nP ; j++ ){
			if ( flow[i][j] > 0 ){
				if ( flag ) putchar(' ');
				printf("%d", j - nK);
				flag++;
			}
		}
		puts("");
	}
}

int maxFlowEdmonds(){
	int totFlow = 0;
	
	while ( bfs() ){
		for ( int v = snk ; v != src ; v = parent[v] ){
			int u = parent[v];
			flow[u][v] += minCap[snk];
			flow[v][u] -= minCap[snk];
			
			cap[u][v] -= minCap[snk];
			cap[v][u] += minCap[snk];
		}
		
		totFlow += minCap[snk];
	}
	
	return totFlow;
}

int now[SIZE], L[SIZE];

int maxFlowDinic(){
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

int maxFlow(){ return maxFlowDinic(); }

bool bfs(){
	int q[SIZE];
	int head, tail;
	
	head = tail = 0;
	for ( int i = 0 ; i < N ; i++ ) parent[i] = -1, minCap[i] = INT_MAX, L[i] = -1;
	L[src] = 0;
	q[tail++] = src;
	
	while ( head != tail ){
		int u = q[head++];
		/*printf("-> %d %d %d\n", u, parent[u], minCap[u]);*/
		if ( u == snk ) return true;
		
		for ( int i = 0 ; i < N ; i++ ){
			if ( L[i] < 0 && cap[u][i] > 0 ){
				parent[i] = u;
				minCap[i] = min(cap[u][i], minCap[u]);
				L[i] = L[u] + 1;
				q[tail++] = i;
			}
		}
	}
	
	return false;
}

int dfs(int u, int lim){
	int df;
	
	if ( u == snk ) return lim;
	for ( int &i = now[u] ; i < N ; i++ ){
		if ( cap[u][i] > 0 && L[i] == L[u] + 1 ){
			df = dfs(i, min(cap[u][i], lim));
			if ( df > 0 ){
				cap[u][i] -= df;
				cap[i][u] += df;
				
				flow[u][i] += df;
				flow[i][u] -= df;
				return df;
			}
		}
	}
	
	return 0;
}

