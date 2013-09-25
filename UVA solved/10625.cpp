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

llu goo[100][100];

void printArr(llu arr[100][100], int size){
	for ( int i = 0 ; i < size ; i++ ){
		for ( int j = 0 ; j < size ; j++ ) cout<<arr[i][j]<<' ';
		cout<<endl;
	}
}

void matrixMult(llu to[100][100], llu one[100][100], llu two[100][100], int size){
	for ( int i = 0 ; i < size ; i++ )
		for ( int j = 0 ; j < size ; j++ ){
			goo[i][j] = 0;
			for ( int k = 0 ; k < size ; k++ ) goo[i][j] += one[i][k] * two[k][j];
		}

	for ( int i = 0 ; i < size ; i++ )
		for ( int j = 0 ; j < size ; j++ )
			to[i][j] = goo[i][j];
}

void matrixExp(llu res[100][100], llu base[100][100], int powr, int size){
	llu temp[100][100];
	
	memset(res, 0, sizeof(res));
	for ( int i = 0 ; i < size ; i++ ) res[i][i] = 1;
	for ( int i = 0 ; i < size ; i++ )
		for ( int j = 0 ; j < size ; j++ )
			temp[i][j] = base[i][j];
	
	while ( powr ){
		if ( powr & 1 ) matrixMult(res, temp, res, size);
		matrixMult(temp, temp, temp, size);
		powr >>= 1;
	}
}

int main(){
	llu base[100][100], res[100][100];
	char ruleGivn[127];
	int size = 126 - 32;
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		while ( test-- ){
			memset(base, 0, sizeof(base));
			int rule, query;
			
			scanf("%d", &rule);
			memset(ruleGivn, 0, sizeof(ruleGivn));
			while ( rule-- ){
				char ch, inp[105], *prod;
				scanf("%s", inp);
				ch = inp[0];
				prod = inp + 3;
				//cout<<ch<<' '<<prod<<endl;
				ruleGivn[ch-33] = 1;
				for ( int i = 0 ; prod[i] ; i++ ) base[prod[i]-33][ch-33]++;
			}

			for ( int i = 0 ; i < size ; i++ )
				if ( ruleGivn[i] == 0 ) base[i][i] = 1;
				
			//printArr(base, size);
			
			scanf("%d", &query);
			while ( query-- ){
				char initial[105], chr[2];
				int n, arr[100];
				
				scanf("%s%s%d", initial, chr, &n);
				memset(arr, 0, sizeof(arr));
				for ( int i = 0 ; initial[i] ; i++ ) arr[initial[i]-33]++;

				memset(res, 0, sizeof(res));
				matrixExp(res, base, n, size);
				//printArr(res, size);
				llu ans = 0;
				
				for ( int i = 0 ; i < size ; i++ ) ans += arr[i] * res[chr[0]-33][i];
				printf("%llu\n", ans);
			}
		}
	}
	
	return 0;
}
/*
4
3
a->babchaubaj
b->kfasbebicoelf
c->oakcoak
3
cabsnabs c 100
b c 15
aa a 5
3
a->babchaubaj
b->kfasbebicoelf
c->oakcoak
1
cabsnabs c 100
3
a->babchaubaj
b->kfasbebicoelf
c->oakcoak
1
b c 15
3
a->babchaubaj
b->kfasbebicoelf
c->oakcoak
1
aa a 5
*/
