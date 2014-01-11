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

llu dp[27][352][27];
int vis[27][352][27], ks = 1;

llu rec(int pos, int remSm, int last){
	llu res = 0;
	int i;
	
	if ( pos == 0 && remSm == 0 ) return 1;
	if ( pos == 0 || remSm <= 0 ) return 0;
	if ( vis[pos][remSm][last] ) return dp[pos][remSm][last];
	vis[pos][remSm][last] = 1;
	
	for ( i = last + 1 ; i <= 26 ; i++ ) res += rec(pos - 1, remSm - i, i);
	
	return dp[pos][remSm][last] = res;
}

int main(){
	int L, S;
	llu res;
	
	while ( scanf("%d%d", &L, &S) != EOF ){
		if ( L == 0 && S == 0 ) break;
		if ( L > 26 || S > 351 ) res = 0;
		else res = rec(L, S, 0);
		printf("Case %d: %llu\n", ks++, res);
	}
	
	return 0;
}

