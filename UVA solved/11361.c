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

char lo[12], hi[12];
long dp[12][2][2][90][90], K;
int vis[12][2][2][90][90], ks;

long rec(int pos, int le, int ge, int modN, int modS){
	long res = 0;
	int nle, nge, i, nModN, nModS;
	
	if ( pos == 10 ) return (modN == 0 && modS == 0);
	if ( vis[pos][le][ge][modN][modS] == ks ) return dp[pos][le][ge][modN][modS];
	vis[pos][le][ge][modN][modS] = ks;

 	modN *= 10;
	for ( i = 0 ; i < 10 ; i++ ){
		nle = le, nge = ge;
		
		if ( le == 0 && lo[pos] < i + '0' ) nle = 1;
		if ( le == 0 && lo[pos] > i + '0' ) continue;
		
		if ( ge == 0 && hi[pos] > i + '0' ) nge = 1;
		if ( ge == 0 && hi[pos] < i + '0' ) continue;

		nModN = (modN + i) % K, nModS = (modS + i) % K;
		
		res += rec(pos + 1, nle, nge, nModN, nModS);
	}
	
	modN /= 10;
	return dp[pos][le][ge][modN][modS] = res;
}

int main(){
	long a, b;
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld%ld%ld", &a, &b, &K);
			if ( K >= 90 ){ puts("0"); continue; }
			sprintf(lo, "%010ld", a);
			sprintf(hi, "%010ld", b);
			printf("%ld\n", rec(0, 0, 0, 0, 0));
		}
	}
	
	return 0;
}

