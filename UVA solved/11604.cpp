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

int N;
char code[101][22];
int vis[101][22];

int dfs(int cd, int idx){
	vis[cd][idx] = 1;
	//printf("%d %d\n", cd, idx);
	for ( int i = 0 ; i < N ; i++ ){
		if ( cd == i ) continue;
		int j;
		for ( j = 0 ; code[cd][idx + j] && code[cd][idx + j] == code[i][j] ; j++ );
		
	//	printf("Comparison between %d,%d and %d, 0 ended at %d\n", cd, idx, i, j);
		if ( code[cd][idx + j] == 0 ){
		//	printf("%d th string ended, now going to %d %d\n", cd, i, j);
			if ( code[i][j] == 0 ) return 1;
			if ( vis[i][j] == 0 && dfs(i, j) ) return 1;
		}
		else if ( code[i][j] == 0 ){
		//	printf("%d th string ended midway, now going to %d %d\n", i, cd, idx + j);
			if ( vis[cd][idx + j] == 0 && dfs(cd, idx + j) ) return 1;
		}
	}
	
	vis[cd][idx] = 2;
	return 0;
}

int checkCode(){
	int flag = 0;
	
	memset(vis, 0, sizeof(vis));
	for ( int i = 0 ; i < N ; i++ ){
		if ( vis[i][0] == 0 ) flag = dfs(i, 0);
		if ( flag ) return 0;
	}
	
	return 1 - flag;
}

int main(){
	int ks = 1;
	ios::sync_with_stdio(true);
	
	while ( cin >> N && N > 0 ){
		for ( int i = 0 ; i < N ; i++ ){
			cin >> code[i];
			cin >> code[i];
		}
		
		printf("Case #%d: ", ks++);
		printf("%s\n", checkCode() ? "Not ambiguous." : "Ambiguous.");
	}
	
	return 0;
}

