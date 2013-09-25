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

using namespace std;

typedef long long ll;
typedef unsigned long long llu;

#define MARGIN 32000L
long ks, n, final;
int vis[101][1<<16], turn = 1;
char possible[101][1<<16];
long toNext[101][1<<16];
long arr[101];

int inRange(long val){
	return ( val >= -32000 && val <= 32000 );
}

char findPossible(int pos, long val){
	long temp;
	char res = 0;
	
	if ( inRange(val) == 0 ) return 0;
	if ( pos == n ) return (val == final) ? '=' : 0;
	if ( vis[pos][MARGIN + val] == turn ) return possible[pos][MARGIN + val];
	
	vis[pos][MARGIN + val] = turn;
	
	temp = val + arr[pos];
	if ( inRange(temp) && findPossible(pos + 1, temp) ){
		res = '+';
		toNext[pos][MARGIN + val] = MARGIN + temp;
	}

	if ( !res ){
		temp = val - arr[pos];
		if ( inRange(temp) && findPossible(pos + 1, temp)){
			res = '-';
			toNext[pos][MARGIN + val] = MARGIN + temp;
		}
	}

	if ( !res ){
		temp = val * arr[pos];
		if ( inRange(temp) && findPossible(pos + 1, temp)){
			res = '*';
			toNext[pos][MARGIN + val] = MARGIN + temp;
		}
	}

	if ( !res && arr[pos] && ( val % arr[pos] == 0 ) ){
		temp = val / arr[pos];
		if ( inRange(temp) && findPossible(pos + 1, temp)){
			res = '/';
			toNext[pos][MARGIN + val] = MARGIN + temp;
		}
	}

	return possible[pos][MARGIN + val] = res;
}

void printExp(int pos, long val){
	if ( pos == n ){
		printf("=%ld\n", final);
		return;
	}
	
	printf("%c%ld", possible[pos][MARGIN + val], arr[pos]);
	printExp(pos + 1, toNext[pos][MARGIN + val] - MARGIN);
}

int main(){
	int test;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%ld", &n);
			for ( int i = 0 ; i < n ; i++ ) scanf("%ld", &arr[i]);
			scanf("%ld", &final);
			
			if ( findPossible(1, arr[0]) ){
				printf("%ld", arr[0]);
				printExp(1, arr[0]);
			}
			else puts("NO EXPRESSION");
			turn++;
		}
	}
	
	return 0;
}

