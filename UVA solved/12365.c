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

ll tree[100005], arr[100005], power[100005];
long N;
ll B, P;

ll extgcd (ll a, ll b, ll *x, ll *y) {
	ll d = a;
	if (b != 0) {
		d = extgcd(b, a % b, y, x);
		*y -= (a/b) * (*x);
	} else {
		*x = 1; *y = 0;
	}
	return d;
}

ll mod_inverse (ll a, ll m) {
	ll x, y;
	
	extgcd(a, m, &x, &y);
	return (m + x % m) % m;
}

void update(long ind, ll val){
	long i = ind;
	
	while ( i <= N ){
		tree[i] = ( tree[i] + P - arr[ind] );
		if ( tree[i] >= P ) tree[i] -= P;
		i += i & -i;
	}
	
	i = ind;
	arr[ind] = val % P;
	while ( i <= N ){
		tree[i] = (tree[i] + val);
		if ( tree[i] >= P ) tree[i] -= P;
		i += i & -i;
	}
}

ll read(long ind){
	ll sum = 0;
	
	while ( ind ){
		sum = (sum + tree[ind]);
		if ( tree[ind] >= P ) tree[ind] -= P;
		ind -= ind & -ind;
	}
	
	return sum;
}

int main(){
	long q, j, i;
	ll tmp, v, res, rawRes;
	char cmd[2];
	
	while ( scanf("%lld%lld%ld%ld", &B, &P, &N, &q) == 4 ){
		if ( B == 0 && P == 0 && N == 0 && q == 0 ) break;
		N++;
		memset(tree, 0, sizeof(tree));
		memset(arr, 0, sizeof(tree));
		
		power[0] = 1;
		for ( i = 1 ; i <= N ; i++ ) power[i] = ( power[i-1] * B ) % P;
		
		while ( q-- ){
			scanf("%s", cmd);
			if ( cmd[0] == 'E' ){
				scanf("%ld%lld", &i, &v);
				i++;
				tmp = power[N-i];
				tmp *= v;
				tmp %= P;
				update(i, tmp);
			}
			else if ( cmd[0] == 'H' ){
				scanf("%ld%ld", &i, &j);
				i++, j++;
				
				tmp = (read(j) - read(i - 1)) % P;
				if ( tmp < 0 ) tmp += P;
				
				res = tmp * mod_inverse(power[N-j],P);
				res %= P;
				printf("%lld\n", res);
			}
		}
		
		puts("-");
	}
	
	return 0;
}

