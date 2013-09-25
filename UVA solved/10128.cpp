#include <cstdio>
#include <cstring>

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

ll X[14][14], nCr[14][14];
ll tmp[14][14][1<<13][14];
int vis[14][14][1<<13][14], Turn;
int n, l, r;

ll dp(int total, int pos, int seen, int mux, int last){ // queue forming, 'total' people, in 'pos'
	ll res = 0;
	
	if ( pos == 0 ) return ( seen == 0 );
	if ( vis[pos][seen][mux][last] == Turn ) return tmp[pos][seen][mux][last];
	
	vis[pos][seen][mux][last] = Turn;
	for ( int i = 0 ; i < total ; i++ ){
		if ((mux & (1<<i)) == 0){
			if ( last < (1+i) && seen ) res += dp(total, pos - 1, seen - 1, mux | (1<<i), i + 1);
			else if ( last > ( 1 + i ) ) res += dp(total, pos - 1, seen, mux | (1<<i), last);
		}
	}
	
	return tmp[pos][seen][mux][last] = res;
}

ll rec(int seen, int unseen){ // how many ways can a queue be formed, where seen peoples are seen and rest are unseen
	if ( X[seen][unseen] == -1 ){
		Turn++;
		X[seen][unseen] = dp(seen + unseen, seen + unseen, seen, 0, 0);
	}
	
	return X[seen][unseen];
}

int main(){
	int test;
	
	for ( int i = 0 ; i < 14 ; i++ ) nCr[i][0] = 1;
	for ( int i = 1 ; i < 14 ; i++ )
		for ( int j = 1 ; j < 14 ; j++ ) nCr[i][j] = nCr[i-1][j] + nCr[i-1][j-1];
		
	memset(X, -1, sizeof(X));
	
	while ( scanf("%d", &test) == 1 ){
		for ( int ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d%d", &n, &l, &r);
			l--, r--;
			ll res = 0;
			for ( int i = l ; i <= n - 1 - r ; i++ )
				res += rec(l, i - l) * rec(r, n - 1 - r - i ) * nCr[n-1][i];

			printf("%lld\n", res);
		}
	}
	
	return 0;
}

