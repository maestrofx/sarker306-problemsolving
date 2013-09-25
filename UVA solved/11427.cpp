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

double dp1[101][101], dp[2001];
int vis1[101][101], ks;
int n, nom, den;

double rec(int l, int w){
	if ( l + w == n ){
		return w*den > nom*(w+l) ? 1.0 : 0.0;
	}
	
	else if ( w*den > nom*(w+l) ){
		return 1.0;
	}
	
	if ( vis1[l][w] == ks ) return dp1[l][w];
	vis1[l][w] = ks;
	
	return dp1[l][w] = ((den-nom) * rec(l+1, w) + nom * rec(l, w+1)) / den;
}

int main(){
	int test;
	double avg;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d/%d%d", &nom, &den, &n);
			dp[0] = 1;
			for ( int i = 1 ; i <= 2000 ; i++ ){
				dp[i] = nom * dp[i-1] + (den - nom) * rec(1, 0) * dp[i-1];
				dp[i] /= den;
			}
			
			avg = 0;
			for ( int i = 1 ; i <= 2000 ; i++ ) avg += (dp[i-1]-dp[i]) * i;
			/* dp[i-1] - dp[i] stands for the probability that I'll stop exactly in day i */
			/* dp[i] means I'll win upto ith day. (1-dp[i]) means I won't.
			   dp[i-1] means I'll win upto i-1 th day. */
			
			printf("Case #%d: %d\n", ks, (int)(avg + 1e-6));
		}
	}
	
	return 0;
}

