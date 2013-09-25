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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

int row, col;
llu val[1005][1005];

int gcd(int m, int n){
	int tmp;

	while ( n ){
		tmp = m;
		m = n;
		n = tmp % n;
	}

	return m;
}

llu nC3(int n){
	llu res = n;
	
	res *= (n-1);
	res >>= 1;
	res *= (n-2);
	res /= 3;
	
	return res;
}

void precalc(){
	int i, j;
	
	for ( i = 0 ; i < 1001 ; i++ )
		for ( j = i ; j < 1001 ; j++ )
			val[j][i] = val[i][j] = gcd(j, i);
}

llu calc(){
	llu res = 0;
	
	for ( int i = 1 ; i <= row ; i++ )
		for ( int j = 1 ; j <= col ; j++ )
			res += (val[i][j] - 1) * (row-i+1) * (col-j+1);

	return nC3((1+row) * (1+col)) - (row+1)*nC3(1+col) - (col+1)*nC3(1+row) - (res<<1);
}

llu brute(){
	llu res = 0;
	
	for ( int i = 0 ; i <= row ; i++ )
		for ( int j = 0 ; j <= col ; j++ )
			for ( int k = 0 ; k <= row ; k++ )
				for ( int l = 0 ; l <= col ; l++ ){
					if ( k == i && j == l ) continue;
					for ( int m = 0 ; m <= row ; m++ )
						for ( int n = 0 ; n <= col ; n++ ){
							if ((k==m && l==n)||(i==m && j==n)) continue;
							if ( (n-l)*(k-i) == (m-k)*(l-j) ) continue;
							res++;
						}
				}

	return res/6;
}

int main(){
	int ks = 1;
	
	precalc();
	while ( cin >> row >> col ){
		if ( row == 0 && col == 0 ) break;
		
		printf("Case %d: %llu\n", ks++, calc());
		//cout<<brute()<<endl;
	}
	
	return 0;
}

