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

int n, sz[5], ks;
char vis[5][5][5][5][8][8][8][8];
unsigned dp[5][5][5][5][8][8][8][8];

unsigned rec(int fColor, int fSz, int lColor, int lSz, int* rem){
	unsigned res = 0;
	int total = 0;
	
	for ( int i = 1 ; i <= n ; i++ ) total += rem[i];
	if ( total == 0 ){
		if ( fColor == 0 || ( fColor != lColor && fSz != lSz )) return 1;
		return 0;
	}

	if ( vis[fColor][fSz][lColor][lSz][rem[1]][rem[2]][rem[3]][rem[4]] )
		return dp[fColor][fSz][lColor][lSz][rem[1]][rem[2]][rem[3]][rem[4]];
	vis[fColor][fSz][lColor][lSz][rem[1]][rem[2]][rem[3]][rem[4]] = 1;
	
	for ( int i = 1 ; i <= n ; i++ ){
		if ( i == lColor ) continue;
		for ( int j = 1 ; j < 4 ; j++ ){
			if ( j == lSz ) continue;
			if ( rem[i] < j ) break;
			rem[i] -= j;
			if ( fColor == 0 & fSz == 0 ) res += rec(i, j, i, j, rem);
			else res += rec(fColor, fSz, i, j, rem);
			rem[i] += j;
		}
	}
	
	return dp[fColor][fSz][lColor][lSz][rem[1]][rem[2]][rem[3]][rem[4]] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			memset(sz, 0, sizeof(sz));
			for ( int i = 1 ; i <= n ; i++ ) scanf("%d", &sz[i]);
			
			printf("%lu\n", rec(0,0,0,0,sz));
		}
	}
	
	return 0;
}

