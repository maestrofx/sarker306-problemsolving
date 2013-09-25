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

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)
#define SIZE 30002

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int MAX(int a, int b) { return a > b ? a : b; }
int arr[SIZE], n;
int lChld(int node){ return 1 + (node<<1); }
int rChld(int node) { return ( 1 + node )<<1; }
int lo, hi;

int query(int *tree, int node, int left, int right){
	int mid = ( left + right ) >> 1, lc = lChld(node), rc = rChld(node);
	
	if ( lo > right || hi < left ) return INT_MIN;
	if ( left >= lo && right <= hi ) return tree[node];
	return MAX( query(tree, lc, left, mid), query(tree, rc, mid + 1, right) );
}

void update(int *tree, int node, int left, int right, int val){
	int mid = ( left + right ) >> 1, lc = lChld(node), rc = rChld(node);

	if ( lo > right || hi < left ) return;
	if ( left == right ){
		tree[node] = val;
		return;
	}
	
	update(tree, lc, left, mid, val);
	update(tree, rc, mid + 1, right, val);
	tree[node] = MAX(tree[rc], tree[lc]);
}

int upTree[SIZE<<2], downTree[SIZE<<2], bal[SIZE<<2];

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		while ( test-- ){
			scanf("%d", &n);
			vector<int> sorted;
			for ( int i = 1 ; i <= n ; i++ ){
				scanf("%d", arr + i);
				sorted.pb(arr[i]);
			}
			
			sort(sorted.begin(), sorted.end());
			for ( int i = 1 ; i <= n ; i++ ){
				arr[i] = upper_bound(sorted.begin(), sorted.end(), arr[i]) - sorted.begin();
			}
			
			arr[n + 1] = n + 1;
			n++;
			
			memset(upTree, 0, sizeof(upTree));
			memset(downTree, 0, sizeof(downTree));
			
			for ( int i = 1 ; i < n ; i++ ){
				lo = arr[i] + 1, hi = n;
				int val1 = query(upTree, 0, 0, n);
				lo = 0, hi = arr[i] - 1;
				int val2 = query(downTree, 0, 0, n);
				
				lo = hi = arr[i];

				update(downTree, 0, 0, n, val1 = val1 + (val1 % 2 == 1));
				update(upTree, 0, 0, n, val2 = val2 + (val2 % 2 == 0));
			}
			
			lo = 0, hi = n;
			printf("%d\n", MAX(query(upTree, 0, 0, n), query(downTree, 0, 0, n)));
		}
	}
	
	return 0;
}

