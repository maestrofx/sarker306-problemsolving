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

#define SIZE 1005

list<int> adj[SIZE];
int nodes;

int start[SIZE], low[SIZE], parent[SIZE];
int GLTime;

void init(){
	for ( int i = 0 ; i <= nodes ; i++ ) start[i] = low[i] = 0, parent[i] = -1;
	GLTime = 0;
}

struct Edge{
	int u, v;

	Edge(int x = 0, int y = 0) : u(x), v(y) {}
};

stack<Edge>stck;

void dfs(int u){
	low[u] = start[u] = ++GLTime;
	
	for ( list<int>::iterator ptr = adj[u].begin() ; ptr != adj[u].end() ; ptr++ ){
		int v = *ptr;
		
		if ( v != parent[u] && start[v] < start[u] ){
			Edge temp(u, v);
			stck.push(temp);
		}
		
		if ( start[v] == 0 ){
			parent[v] = u;
			dfs(v);
			
			if ( low[v] >= start[u] ){
				Edge temp;
				int cnt = 0;
				
				do {
					cnt++;
					temp = stck.top();
					stck.pop();
					printf("%d %d\n" , temp.u, temp.v);
				}while ( (temp.u != u || temp.v != v) && (temp.u != v || temp.v != u));
				
				if ( cnt == 1 ){
					printf("%d %d\n", v, u);
				}
			}
			
			if ( low[u] > low[v] ) low[u] = low[v];
		}
		else if ( v != parent[u] && start[v] < low[u] ) low[u] = start[v];
	}
}

int main(){
	int m, kase = 1;
	
	while ( scanf("%d%d", &nodes, &m) == 2 ){
		if ( nodes == 0 && m == 0 ) break;
		printf("%d\n\n", kase++);
		
		while ( m-- ){
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].pb(v);
			adj[v].pb(u);
		}
		
		init();
		for ( int i = 1 ; i <= nodes ; i++ ){
			if ( parent[i] == -1 ){
				dfs(i);
			}
		}
		
		for ( int i = 0 ; i <= nodes ; i++ ) adj[i].clear();
		puts("#");
	}
	
	return 0;
}

