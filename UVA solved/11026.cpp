// 11026.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include <stdlib.h>

typedef long long ll;
int n;
ll MOD;

ll dp[1001][1001], cum[1001][1001];
int arr[1001];

void iterative(int n){
	int i, j;

	for ( i = 1 ; i <= n ; i++ ){
		dp[i][1] = arr[i] % MOD;
		cum[i][1] = cum[i-1][1] + dp[i][1];
		if ( cum[i][1] >= MOD ) cum[i][1] -= MOD;
	}

	for ( j = 2 ; j <= n ; j++ ){
		for ( i = 1 ; i <= n ; i++ ){
			dp[i][j] = (cum[n][j-1] - cum[i][j-1] + MOD) % MOD;
			dp[i][j] = ( dp[i][j] * arr[i] ) % MOD;
			cum[i][j] = cum[i-1][j] + dp[i][j];
			if ( cum[i][j] >= MOD ) cum[i][j] -= MOD;
		}
	}
}

int main(int argc, char* argv[]){
	int i, j;
	ll maximum, temp;

	while ( scanf("%d%d", &n, &MOD) == 2 ){
		if ( n == 0 && MOD == 0 ) break;
		
		for ( i = 1 ; i <= n ; i++ ) scanf("%d", &arr[i]);
		maximum = 0;
		
		iterative(n);

		for ( i = 1 ; i <= n ; i++ ){
			temp = 0;
			for ( j = 1 ; j <= n ; j++ ){
				temp = temp + dp[j][i];
				if ( temp >= MOD ) temp -= MOD;
			}
			if ( maximum < temp ) maximum = temp;
		}

		printf("%lld\n", maximum);
	}

	return 0;
}
