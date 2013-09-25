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

char arr[205];
ll maxNum[205];

int main(){
	int test, len;
	
	while ( scanf("%d", &test) == 1 ){
		while ( test-- ){
			scanf("%s", arr);
			for ( len = 0 ; arr[len] ; len++ );
			maxNum[len] = 0;
			for ( int i = len - 1; i >= 0 ; i-- ){
				ll res = LLONG_MIN;
				ll partial = 0;
				for ( int j = i ; arr[j] ; j++ ){
					partial = 10 * partial + arr[j] - '0';
					if ( arr[i] == arr[j] && arr[j] == '0' && j > i ) break;
					if ( partial <= (1LL << 31) - 1 && res < partial + maxNum[j+1] )
						res = partial + maxNum[j+1];
				}
				
				maxNum[i] = res;
			}
			
			printf("%lld\n", maxNum[0]);
		}
	}
	
	return 0;
}

