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

int n, k;
vector<int>flights[100];
int adj[12][12];
int dp[1001][12];
int vis[1001][12], ks;

int rec(int day, int city){
	int res = INT_MAX, temp;
	
	if ( day == k ) return (city == n) ? 0 : INT_MAX;
	if ( vis[day][city] == ks ) return dp[day][city];
	vis[day][city] = ks;
	
	for ( int i = 1 ; i <= n ; i++ ){
		if ( city == i ) continue;
		if ( adj[city][i] == -1 ) continue;
		int flightToday = day % flights[adj[city][i]].size();
		if ( flights[adj[city][i]][flightToday] == 0 ) continue;
		
		temp = rec(day + 1, i);
		if ( temp != INT_MAX ){
			temp += flights[adj[city][i]][flightToday];
			if ( res > temp ) res = temp;
		}
	}
	
	return dp[day][city] = res;
}

int main(){
	while ( scanf("%d%d", &n, &k) == 2 ){
		if ( n == k && n == 0 ) break;
		
		int flightCnt = 0;
		for ( int i = 1 ; i <= n ; i++ ){
			for ( int j = 1 ; j <= n ; j++ ){
				adj[i][j] = -1;
				if ( j == i ) continue;
				int x, cst;
				scanf("%d", &x);
				while ( x-- ){
					scanf("%d", &cst);
					flights[flightCnt].pb(cst);
				}
				
				adj[i][j] = flightCnt;
				flightCnt++;
			}
		}
		
		printf("Scenario #%d\n", ++ks);
		int res = rec(0, 1);
		if ( res == INT_MAX ) puts("No flight possible.\n");
		else printf("The best flight costs %d.\n\n", res);
		for ( int i = 0 ; i < flightCnt ; i++ ) flights[i].clear();
	}
	
	return 0;
}

