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

struct Vector{
	double x, y;
	
	void scan(){ scanf("%lf%lf", &x, &y); }
	bool operator>(const Vector &p){
		return y > p.y;
	}
	
	Vector operator+(const Vector &p){
		Vector tmp;
		tmp.x = x + p.x, tmp.y = y + p.y;
		return tmp;
	}
	
	Vector operator-(const Vector &p){
		Vector tmp;
		tmp.x = x - p.x, tmp.y = y - p.y;
		return tmp;
	}
	
	Vector operator*(const double t){
		Vector tmp;
		tmp.x = x * t, tmp.y = y * t;
		return tmp;
	}
};

Vector lines[100000][2], nil;
int nl, np;

int intersectSegmentVertically(Vector& start, Vector& end, Vector& src, Vector &res){
	double t = (src.x - start.x) / (end.x - start.x);
	
	if ( t < 0 || t > 1 ) return 0;
	res = start + ( end - start ) * t;
	return 1;
}

int waterFalls(Vector &src){
	int last = -1;
	
	while ( src.y > 0 ){
		Vector maxVectorUnderSrc;
		int maxVectorInd = -1;
		maxVectorUnderSrc.x = maxVectorUnderSrc.y = -10000.0;
		
		for ( int i = 0 ; i < nl ; i++ ){
			if ( fabs(lines[i][0].x - lines[i][1].x) < 1e-6 ) continue;
			Vector tmp;
			if ( intersectSegmentVertically(lines[i][0], lines[i][1], src, tmp) ){
				if ( src > tmp && tmp > maxVectorUnderSrc ){
					maxVectorUnderSrc = tmp;
					maxVectorInd = i;
				}
			}
		}
		
		if ( maxVectorInd == -1 ) break;
		if ( lines[maxVectorInd][0].y < lines[maxVectorInd][1].y ) src = lines[maxVectorInd][0];
		else src = lines[maxVectorInd][1];
		last = maxVectorInd;
	}
	
	if ( src.y < 0 ){
		double t = lines[last][0].y / ( lines[last][0].y - lines[last][1].y );
		src = lines[last][0] + (lines[last][1] - lines[last][0] ) * t;
	}
	
	return (int)(src.x);
}

int main(){
	int test, ks;
	Vector src;
	
	nil.x = nil.y = -1e10;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			if ( ks > 1 ) puts("");
			scanf("%d", &nl);
			for ( int i = 0 ; i < nl ; i++ ){
				lines[i][0].scan(), lines[i][1].scan();
				if ( lines[i][0].x < lines[i][1].x ){
					Vector tmp = lines[i][0];
					lines[i][0] = lines[i][1];
					lines[i][1] = tmp;
				}
			}
			
			scanf("%d", &np);
			while ( np-- ){
				src.scan();
				printf("%d\n", waterFalls(src));
			}
		}
	}
	
	return 0;
}
/*
1

4
14 7 3 4
11 13 16 11
1 10 6 7
2 1 4 3
3
10 4
14 14
2 13
*/
