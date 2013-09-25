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

char word[10002], pat[102];
llu ways[10002][102];
int vis[10002][102], ks = 1;

llu rec(int x, int y){
	llu res = 0;
	
	if ( word[x] == 0 && pat[y] == 0 ) return 1;
	if ( word[x] == 0 && pat[y] ) return 0;
	if ( vis[x][y] == ks ) return ways[x][y];
	
	vis[x][y] = ks;
	res += rec(x + 1, y);
	if ( pat[y] == word[x] ) res += rec(x + 1, y + 1);
	return ways[x][y] = res % 1000;
}

int main(){
	
	while ( scanf("%s%s", word, pat) == 2 ){
		printf("%llu\n", rec(0, 0));
		ks++;
	}
	
	return 0;
}

