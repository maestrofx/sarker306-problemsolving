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

/********** suffix array ****************/
#define SIZE 1000005
#define LGSZ 20

namespace SuffixArray{
	int P[LGSZ][SIZE];
	int row, len;
	struct entry{
		int nr[2], p;
		bool operator==(entry &b){ return (nr[0] == b.nr[0] && nr[1] == b.nr[1]); }
	};

	entry L[SIZE];

	int cmp(const entry &a, const entry &b){
		if ( a.nr[0] == b.nr[0] ) return a.nr[1] < b.nr[1];
		return a.nr[0] < b.nr[0];
	}

	void initSuffixArray(char *str){
		int k, i, j, cnt;

		len = strlen(str);
		for ( i = 0 ; i < len ; i++ ) P[0][i] = str[i];

		for ( row = 1, cnt = 1 ; (cnt >> 1) < len ; k++, cnt <<= 1 ){
			for ( i = 0 ; i < len ; i++ ){
				L[i].nr[0] = P[row-1][i];
				L[i].nr[1] = ( cnt + i < len ) ? P[row - 1][cnt + i] : -1;
				L[i].p = i;
			}

			sort(L, L + len, cmp);
			for ( i = 0 ; i < len ; i++ ){
				P[row][L[i].p] = (i > 0 && L[i] == L[i - 1]) ? P[row][L[i-1].p] : i;
			}
		}
		/*for ( k = row - 1, i = 0 ; i < len ; i++ ) puts(str + L[i].p);*/
	}

	int findOccurance(char *src, char *str){
		int lo = 0, hi = len, mid, i;

		while ( lo + 1 < hi ){
			mid = ( lo + hi ) >> 1;
			if ( strcmp(src + L[mid].p, str) >= 0 ) hi = mid;
			else lo = mid;
		}

		src += L[hi].p;
		for ( i = 0 ; src[i] && *str ; i++, str++ ) if ( src[i] != *str ) return -1;
		if ( *str ) return -1;
		return hi;
	}

	int lcp(int x, int y){
		int k, ret = 0;
		if (x == y) return N - x;
		for (k = row - 1; k >= 0 && x < N && y < N; k --)
			if (P[k][x] == P[k][y])
				x += 1 << k, y += 1 << k, ret += 1 << k;
				
		return ret;
	}
};
/****************************************/

char inp[SIZE], pat[SIZE];

int main(){
	int test, q;
	
	ios::sync_with_stdio(true);

	scanf("%d", &test);
	while ( test-- ){
		scanf("%s", inp);
		SuffixArray::initSuffixArray(inp);
		
		scanf("%d", &q);
		while ( q-- ){
   			scanf("%s", pat);
			int res = SuffixArray::findOccurance(inp, pat);
			if ( res >= 0 ) puts("y");
			else puts("n");
		}
	}
	
	return 0;
}

