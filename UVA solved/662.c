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
#define INF 1<<26
typedef unsigned long long llu;
typedef long long ll;

int dp[202][30][202];
int vis[202][30][202], Turn;
long par[202][30][202];
long dist[202], n, k;
int assignedDepo[202];

void produceSoln(int pos, int rem, int last){
	if ( pos > n ) return;
	assignedDepo[pos] = par[pos][rem][last] % 1000;
	produceSoln(pos + 1, par[pos][rem][last] / 1000, assignedDepo[pos]);
}

long rec(int pos, int rem, int last){
	long res = INF, temp, nnext, i;
	
	/*printf ("In %d %d %d\n", pos, rem, last);*/
	if ( pos > n ) return 0;
	if ( rem < 0 ) return INF;
	if ( vis[pos][rem][last] == Turn ) return dp[pos][rem][last];
	vis[pos][rem][last] = Turn;
	
	if ( last ){
		temp = abs(dist[last] - dist[pos]) + rec(pos + 1, rem, last);
		if ( res > temp ){
			res = temp;
			par[pos][rem][last] = 1000 * rem + last;
		}
	}
	
	if ( rem )
	for ( i = pos ; i <= n ; i++ ){
		temp = abs(dist[i] - dist[pos]) + rec(pos + 1, rem - 1, i);
		if ( res > temp ){
			res = temp;
			par[pos][rem][last] = (rem - 1)*1000 + i;
		}
	}
	
/*	printf("%d %d %d -> %d\n", pos, rem, last, res);*/
	return dp[pos][rem][last] = res;
}

int main(){
	int i, j, start, end;
	long res;
	
	while ( scanf("%d%d", &n, &k) == 2 ){
		++Turn;
		if ( n == 0 && k == 0 ) break;
		for ( i = 1 ; i <= n ; i++ ) scanf("%d", &dist[i]);
		if ( dist[1] <= 0 ){
			for ( i = 2 ; i <= n ; i++ ) dist[i] -= dist[1] - 1;
			dist[1] = 1;
		}
		
		printf("Chain %d\n", Turn);

		res = rec(1, k, 0);
		produceSoln(1, k, 0);
		start = end = j = 1;
		for ( i = 1 ; i <= n ; i++ ){
			if ( assignedDepo[start] != assignedDepo[i] ){
				printf("Depot %d at restaurant %d serves restaurant", j++, assignedDepo[start]);
				if ( start != end ) printf("s %d to %d\n", start,end);
				else printf(" %d\n", start);
				start = end = i;
			}
			else end = i;
		}
		
		printf("Depot %d at restaurant %d serves restaurant", j++, assignedDepo[start]);
		if ( start != end ) printf("s %d to %d\n", start,end);
		else printf(" %d\n", start);
		printf("Total distance sum = %ld\n\n", res);
	}
	
	return 0;
}

