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

int N;
int adj[26][2], final[26];
llu dp[26][32];
int vis[26][32], ks;

llu rec(int pos, int rem){
	llu res = 0;
	
	if ( rem == 0 ) return final[pos];
	if ( vis[pos][rem] == ks ) return dp[pos][rem];
	vis[pos][rem] = ks;
	
	res = rec(adj[pos][0], rem - 1) + rec(adj[pos][1], rem - 1);
	return dp[pos][rem] = res;
}

int main(){
	char now[2], to0[2], to1[2], isF[2];
	int M, i;
	
	while ( scanf("%d", &N) == 1 ){
		for ( i = 0 ; i < N ; i++ ){
			scanf("%s%s%s%s", now, to0, to1, isF);
			adj[now[0] - 'A'][0] = to0[0] - 'A';
			adj[now[0] - 'A'][1] = to1[0] - 'A';
			final[now[0] - 'A'] = (isF[0] == 'x') ? 1 : 0;
		}
		
		scanf("%d", &M);
		ks++;
		printf("%llu\n", rec(0, M));
	}
	
	return 0;
}

