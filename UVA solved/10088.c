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

long poly[1002][2];
int n;

long gcd(long m, long n){
	long tmp;

	while ( n ){
		tmp = m;
		m = n;
		n = tmp % m;
	}

	return m;
}

int main(){
	int i;
	long boundary, area_2;
	
	/* A = P + B/2 - 1 => 2A + 2 - B = 2P */
	while ( scanf("%d", &n) == 1 && n > 0 ){
		boundary = area_2 = 0;
		for ( i = 0 ; i < n ; i++ ) scanf("%ld%ld", &poly[i][0], &poly[i][1]);
		poly[n][0] = poly[0][0], poly[n][1] = poly[0][1];
		for ( i = 0 ; i < n ; i++ ){
			boundary += gcd(abs(poly[i][0] - poly[i+1][0]), abs(poly[i][1] - poly[i+1][1]));
			area_2 += poly[i][0] * poly[i+1][1] - poly[i+1][0] * poly[i][1];
		}
		
		if ( area_2 < 0 ) area_2 = -area_2;
		printf("%ld\n", (area_2 + 2 - boundary)>>1);
	}
	
	return 0;
}

