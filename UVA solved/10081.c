#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

double dp[102][11][11];
char vis[102][11][11];
int alphabets;

double rec(int pos, int last){
	double res = 0;
	
	if ( last < 1 || last > alphabets ) return 0;
	if ( pos == 0 ) return 1.0;
	if ( vis[pos][alphabets][last] ) return dp[pos][alphabets][last];
	vis[pos][alphabets][last] = 1;

	res = rec(pos - 1, last) + rec(pos - 1, last + 1) + rec(pos - 1, last - 1);
	res /= 1.0 * alphabets;
	
	return dp[pos][alphabets][last] = res;
}

int main(){
	int n, i;
	double res;
	
	while ( scanf("%d%d", &alphabets, &n) == 2 ){
		res = 0;
		alphabets++;
		for ( i = 1 ; i <= alphabets ; i++ ) res += rec(n - 1, i);
		res /= 1.0 * alphabets;
		printf("%.5lf\n", res * 100);
	}
	
	return 0;
}

