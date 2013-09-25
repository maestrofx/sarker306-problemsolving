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

llu ways[66][66][3];
char vis[66][66][3];

enum State{LOCKED = 1, UNLOCKED};

llu rec(int remDwr, int remSec, int lst){
	llu res = 0;
	
	if ( remDwr == 0 && remSec == 0 ) return 1;
	if ( remDwr == 0 || remDwr < remSec) return 0;

	if ( vis[remDwr][remSec][lst] ) return ways[remDwr][remSec][lst];
	vis[remDwr][remSec][lst] = 1;
	
	if ( lst == UNLOCKED ) res += rec(remDwr - 1, remSec, LOCKED) + rec(remDwr - 1, remSec, UNLOCKED);
	else res += rec( remDwr - 1, remSec, UNLOCKED ) + rec( remDwr - 1, remSec - 1, LOCKED );
	return ways[remDwr][remSec][lst] = res;
}

int main(){
	int n, s;
	
	while ( scanf("%d%d", &n, &s) == 2 ){
		if ( n < 0 && s < 0 ) break;
		printf("%llu\n", rec(n, s, 0));
	}
	
	return 0;
}

