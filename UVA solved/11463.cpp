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

int arr[101][101], n;

int main(){
	int m, u, v, test, mx;
	
	while ( scanf("%d", &test) == 1 ){
		for (int ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			
			for ( int i = 0 ; i <= n ; i++ ){
				for ( int j = 0 ; j <= n ; j++ )
					arr[i][j] = 1000000;

				arr[i][i] = 0;
			}

			scanf("%d", &m);
			while ( m-- ){
				scanf("%d%d", &u, &v);
				arr[u][v] = arr[v][u] = 1;
			}
			
			for ( int k = 0 ; k < n ; k++ )
				for ( int i = 0 ; i < n ; i++ )
					for ( int j = 0 ; j < n ; j++ )
						if ( arr[i][j] > arr[i][k] + arr[k][j] )
							arr[i][j] = arr[i][k] + arr[k][j];

			mx = INT_MIN;
			scanf("%d%d", &u, &v);
			for ( int i = 0 ; i < n ; i++ )
				if ( mx < arr[u][i] + arr[i][v] ) mx = arr[u][i] + arr[i][v];

			printf("Case %d: %d\n", ks, mx);
		}
	}
	
	return 0;
}

