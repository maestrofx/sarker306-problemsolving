#include <cstdio>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>

#define FOR(i, a, b) for (i = (a); i <= (b); i++)
#define REP(i, a) for (i = 0; i < (a); i++)
#define ALL(v) (v).begin(), (v).end()
#define SET(a, x) memset((a), (x), sizeof(a))
#define SZ(a) ((int)(a).size())
#define CL(a) ((a).clear())
#define SORT(x) sort(ALL(x))
#define mp make_pair
#define pb push_back
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

#define filer() freopen("in.txt","r",stdin)
#define filew() freopen("out.txt","w",stdout)
#define SIZE 72

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

char grid[20][7];
int xdir[] = {-1, -1, -2, -2};
int ydir[] = {-2, +2, -1, +1};
int n;
int tot;
int base[SIZE][SIZE];
int MOD = 10007;

void matrixMult(int to[SIZE][SIZE], int one[SIZE][SIZE], int two[SIZE][SIZE], int row){
	int tmp[SIZE][SIZE];

	for ( int i = 0 ; i < row ; i++ ){
		for ( int j = 0 ; j < row ; j++ ){
			tmp[i][j] = 0;
			for ( int k = 0 ; k < row ; k++ ) tmp[i][j] = ( tmp[i][j] + one[i][k] * two[k][j] ) % MOD;
		}
	}

	for ( int i = 0 ; i < row ; i++ )
		for ( int j = 0 ; j < row ; j++ ) to[i][j] = tmp[i][j];
}

int matrixExpo(int row, int pwr){
	int tmp[SIZE][SIZE], res[SIZE][SIZE];
	int total = 0;

	if ( pwr == -1 ) return 15;
	if ( pwr == 0 ) return 69;

	for ( int i = 0 ; i < row ; i++ ){
		for ( int j = 0 ; j < row ; j++ ) res[i][j] = 0, tmp[i][j] = base[i][j];
		res[i][i] = 1;
	}

	while ( pwr ){
		if ( pwr & 1 ) matrixMult(res, res, tmp, row);
		matrixMult(tmp, tmp, tmp, row);
		pwr >>= 1;
	}

	for ( int i = 0 ; i < row ; i++ )
		for ( int j = 0 ; j < row ; j++ ) total = ( total + res[i][j] ) % MOD;

	return total;
}

int safe(int r, int c){
	int i, u, v;

	if ( grid[r][c] == '*' ) return 0;
	for ( i = 0 ;  i < 4 ; i++ ){
		u = xdir[i] + r, v = ydir[i] + c;
		if ( u >= 0 && v >= 0 && v < 6 && grid[u][v] == '*' ) return 0;
	}

	return 1;
}

void backTrack(int r, int c, int rem){
	int i;

	if ( r == n ){
		tot++;
	/*	for ( i = 0 ; i < n ; i++ ) puts(grid[i]);
		puts("");*/
		return;
	}

	if ( rem == 0 ) backTrack(r + 1, 0, 2);
	else{
		if ( safe(r, c) ){
			grid[r][c] = '*';
			if ( c + 1 < 6 ) backTrack(r, c + 1, rem - 1);
			else if ( rem == 1 ) backTrack(r + 1, 0, 2);
			grid[r][c] = '-';
		}

		if ( c + 1 < 6 ) backTrack(r, c + 1, rem);
	}
}

vector<int> validRowConf;
map<int, int>validTwoRowConf;

int isConflicting(int a, int b, int c){
	for ( int i = 0 ; i < 6 ; i++ ){
		if ( a & (1<<i) ){
			if ( i + 1 < 6 && (c & (1<<(i+1))) ) return 1;
			if ( i - 1 >= 0 && (c & (1<<(i-1))) ) return 1;
			if ( i + 2 < 6 && (b & (1<<(i+2))) ) return 1;
			if ( i - 2 >= 0 && (b & (1<<(i-2))) ) return 1;
		}
	}

	for ( int i = 0 ; i < 6 ; i++ ){
		if ( b & (1<<i) ){
			if ( i + 2 < 6 && (c & (1<<(i+2))) ) return 1;
			if ( i - 2 >= 0 && (c & (1<<(i-2))) ) return 1;
		}
	}

	return 0;
}

void init(){
	int ind = 0;

	for ( int i = 0 ; i < 64 ; i++ ){
		int cntBit = 0;
		int k = i;
		while ( k ){
			cntBit++;
			k &= k - 1;
		}

		if ( cntBit == 2 ) validRowConf.pb(i);
	}

	for ( int i = 0 ; i < validRowConf.size() ; i++ )
		for ( int j = 0 ; j < validRowConf.size() ; j++ ){
			if ( isConflicting(validRowConf[i], validRowConf[j], 0) == 0 ){
				if ( validTwoRowConf.find(validRowConf[i] * 64 + validRowConf[j]) == validTwoRowConf.end() )
					validTwoRowConf.insert(pair<int, int>(validRowConf[i] * 64 + validRowConf[j], ind++));
			}
		}

	for ( int i = 0 ; i < validRowConf.size() ; i++ )
		for ( int j = 0 ; j < validRowConf.size() ; j++ )
			for ( int k = 0 ; k < validRowConf.size() ; k++ )
				if ( isConflicting(validRowConf[i], validRowConf[j], validRowConf[k]) == 0 ){
					int fir = validTwoRowConf[validRowConf[i] * 64 + validRowConf[j]];
					int sec = validTwoRowConf[validRowConf[j] * 64 + validRowConf[k]];
					base[fir][sec]++;
				}
}

int main(){
	int i, j, test;

	for ( i = 0 ; i < 20 ; i++ )
		for ( j = 0 ; j < 6 ; j++ ) grid[i][j] = '-';

	init();

	while ( scanf("%d", &test) == 1 ){
	    while (test-- ){
	        scanf("%d", &n);
	        /*tot = 0;
            backTrack(0, 0, 2);
            printf("%d\n", tot % MOD);*/
            printf("%d\n",matrixExpo(validTwoRowConf.size(), n - 2));
	    }
    }

	return 0;
}

