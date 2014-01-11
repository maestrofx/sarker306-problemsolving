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

unsigned long N, L, M, d;
unsigned dp[33][2][2];
int vis[33][2][2], ks = 1;

unsigned rec(int pos, int le, int ge){
	int nle, nge;
	unsigned res = 0, i, temp;
	
	if ( pos < 0 ) return 0;
	if ( vis[pos][le][ge] == ks ) return dp[pos][le][ge];
	vis[pos][le][ge] = ks;
	
	for ( i = 1 ; i <= 1 ; i-- ){
		nle = le;
		if ( le == 0 && ((L>>pos)&1) > i ) continue;
		if ( le == 0 && ((L>>pos)&1) < i ) nle = 1;
		
		nge = ge;
		if ( ge == 0 && ((M>>pos)&1) > i ) nge = 1;
		if ( ge == 0 && ((M>>pos)&1) < i ) continue;
		
		temp = (i<<pos) | rec(pos - 1, nle, nge);
		if ((N | res) <= (N | temp)){
			res = temp;
		}
	}
	
	return dp[pos][le][ge] = res;
}

int main(){
	unsigned i;
	while ( scanf("%lu%lu%lu", &N, &L, &M) == 3 ){
		printf("%lu\n", rec(31, 0, 0));

		ks++;
	}
	
	return 0;
}

