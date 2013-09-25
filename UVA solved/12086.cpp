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

#define SIZE 2000005

int arr[SIZE], size;
int val[SIZE];

int read(int ind){
	int sum = 0;
	
	while ( ind ){
		sum += arr[ind];
		ind -= ind & -ind;
	}
	
	return sum;
}

void add(int ind, int x){
	while ( ind <= size ){
		arr[ind] += x;
		ind += ind & -ind;
	}
}

int main(){
	int kase = 1, x, y;
	char command[5];
	
	while ( scanf("%d", &size) == 1 ){
		if ( size == 0 ) break;
		
		if ( kase > 1 ) puts("");
		printf("Case %d:\n", kase++);
		for ( int i = 1 ; i <= size ; i++ ){
			scanf("%d", &val[i]);
			add(i, val[i]);
		}
		
		while ( scanf("%s", command) == 1 ){
			if ( strcmp(command, "END") == 0 ) break;
			scanf("%d%d", &x, &y);
			if ( command[0] == 'S' ){
				add(x, y - val[x]);
				val[x] = y;
			}
			else if ( command[0] == 'M' ) printf("%d\n", read(y) - read(x-1));
		}
		
		memset(arr, 0, sizeof(arr));
	}
	
	return 0;
}

