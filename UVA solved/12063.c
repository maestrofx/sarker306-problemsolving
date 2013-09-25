#include <stdio.h>

typedef long long ll;
typedef unsigned long long llu;

llu dp[101][65][65];
char vis[101][65][65];
int K, N, ks;

llu rec(int mod, int pos, int ones){
	llu res = 0;
	
	/*if ( (ones<<1) > N ) return 0;*/
	if ( pos == N ){
		if ( (ones<<1) == N && mod == 0 ) return 1;
		return 0;
	}
	if ( vis[mod][pos][ones] == ks ) return dp[mod][pos][ones];
	
	vis[mod][pos][ones] = ks;
	mod <<= 1;
	if ( ones ) res += rec( mod % K, pos + 1, ones );
	res += rec ( (mod + 1) % K, pos + 1, ones + 1 );
	
	mod >>= 1;
	return dp[mod][pos][ones] = res;
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &N, &K);
			printf("Case %d: ", ks);
			if ( (N & 1) || K == 0 ) puts("0");
			else printf("%llu\n", rec(1, 1, 1));
		}
	}
	
	return 0;
}

