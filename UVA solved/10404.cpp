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

char arr[1000005];
int moves[15];

int main(){
	int n, k;
	
	while ( cin >> n >> k ){
		for ( int i = 0 ; i < k ; i++ ) cin >> moves[i];
		sort(moves, moves + k);
		memset(arr, 0, sizeof(arr));
		
		for ( int i = 1 ; i <= n ; i++ ){
			for ( int j = 0 ; j < k ; j++ ){
				if ( i - moves[j] < 0 ) break;
				if ( arr[i-moves[j]] == 0 ){
					arr[i] = 1;
					break;
				}
			}
		}
		
		printf("%s wins\n", arr[n] ? "Stan" : "Ollie");
	}
	
	return 0;
}

