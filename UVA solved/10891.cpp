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

int num[100];
int dp[100][100][2];
int vis[100][100][2], ks;
int rec(int l, int r, int who){
	int res, temp, cur = 0, sm = 0;
	
	if ( l > r ) return 0;
	if ( vis[l][r][who] == ks ) return dp[l][r][who];
	vis[l][r][who] = ks;
	
	if ( who == 0 ) res = INT_MIN;
	else res = INT_MAX;

	cur = 0;
	for ( int i = l ; i <= r ; i++ ){
		cur += num[i];
		if ( who == 0 ) temp = cur + rec(i + 1, r, 1);
		else temp = -cur + rec(i + 1, r, 0);
		if ( who == 0 ) res = max(res, temp);
		else res = min(res, temp);
	}

	cur = 0;
	for ( int i = r ; i >= l ; i-- ){
		cur += num[i];
		if ( who == 0 ) temp = cur + rec(l, i - 1, 1);
		else temp = -cur + rec(l, i - 1, 0);
		if ( who == 0 ) res = max(res, temp);
		else res = min(res, temp);
	}

	return dp[l][r][who] = res;
}

int main(){
	int N;
	
	ios::sync_with_stdio(true);
	while ( scanf("%d", &N) == 1 && N > 0 ){
		for ( int i = 0 ; i < N ; i++ ) scanf("%d", &num[i]);
		ks++;
		printf("%d\n", rec(0, N - 1, 0));
	}
	
	return 0;
}

