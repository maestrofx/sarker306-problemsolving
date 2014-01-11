#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)

typedef unsigned long long llu;
typedef long long ll;

long dp[42][21][21][21][2];
char vis[42][21][21][21][2];

int max(int a, int b){ return a > b ? a : b; }

long rec(int pos, int remPeak, int maxPeak, int last, int isDescending){
	long res = 0;
	int nRemPeak;
	
	if ( pos == 0 && remPeak == 0 && last == 0 ) return 1;
	if ( remPeak < 0 ) return 0;
	if ( pos <= 0 ) return 0;
	if ( vis[pos][remPeak][maxPeak][last][isDescending] )
		return dp[pos][remPeak][maxPeak][last][isDescending];
	
	vis[pos][remPeak][maxPeak][last][isDescending] = 1;
	
	if ( last ){
		nRemPeak = ( last == maxPeak && isDescending == 0 ) ? remPeak - 1 : remPeak;
		/*printf("%d %d %d %d %d -> %d %d %d %d %d\n", pos, remPeak, maxPeak, last, isDescending,
			pos - 1, nRemPeak, maxPeak, last - 1, 1);*/
		res += rec(pos - 1, nRemPeak, maxPeak, last - 1, 1);
	}
	
	if ( last + 1 < 21 ){
		/*printf("%d %d %d %d %d -> %d %d %d %d %d\n", pos, remPeak, maxPeak, last, isDescending,
			pos - 1, remPeak, maxPeak, last + 1, 0);*/
		res += rec(pos - 1, remPeak, maxPeak, last + 1, 0);
	}
	
	/*printf("%d %d %d %d %d -> %ld\n", pos, remPeak, maxPeak, last, isDescending, res);*/
	return dp[pos][remPeak][maxPeak][last][isDescending] = res;
}

int main(){
	int n, k, r;
	
	while ( scanf("%d%d%d", &n, &r, &k) == 3 ) printf("%ld\n", rec(n<<1, r, k, 0, 0));
	
	return 0;
}

