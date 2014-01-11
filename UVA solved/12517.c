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

char lim[12];
ll dp[12][2], dp2[12][2];
int vis[12][2], vis2[12][2], ks;

ll rec2(int pos, int eq){
	ll res = 0;
	int i, neq;

	if ( lim[pos] == 0 ) return 1;
	if ( vis2[pos][eq] == ks ) return dp2[pos][eq];
	vis2[pos][eq] = ks;

	for ( i = 0 ; i < 10 ; i++ ){
		neq = eq;
		if ( eq == 0 && lim[pos] < i + '0' ) break;
		if ( eq == 0 && lim[pos] > i + '0' ) neq = 1;
		
		res += rec2(pos + 1, neq);
	}

	return dp2[pos][eq] = res;
}

ll rec(int pos, int eq){
	ll res = 0;
	int i, neq;
	
	if ( lim[pos] == 0 ) return 0;
	if ( vis[pos][eq] == ks ) return dp[pos][eq];
	vis[pos][eq] = ks;
	
	for ( i = 0 ; i < 10 ; i++ ){
		neq = eq;
		if ( eq == 0 && lim[pos] < i + '0' ) break;
		if ( eq == 0 && lim[pos] > i + '0' ) neq = 1;
		
		res += i * rec2(pos + 1, neq) + rec(pos + 1, neq);
	}
	
	return dp[pos][eq] = res;
}

int main(){
	long a, b;
	ll res;
	
	while ( scanf("%ld%ld", &a, &b) == 2 ){
		if ( a == 0 && b == 0 ) break;
		ks++;
		sprintf(lim, "%010ld", b);
		res = rec(0,0);
		ks++;
		if ( a > 1 ){
			sprintf(lim, "%010ld", a - 1);
			res -= rec(0,0);
		}
		
		printf("%lld\n", res);
	}
	
	return 0;
}

