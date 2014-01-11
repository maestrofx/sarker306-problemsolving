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

template<typename T>
class Bit{
private:
	vector<T> tree;
	int size;

public:
	Bit(int _size) : size(_size + 1){
		tree.resize(size + 1, 0);
	}
	
	virtual void add(int ind, T val){
		while ( ind <= size ){
			tree[ind] += val;
			ind += ind & -ind;
		}
	}

	virtual T sum(int ind){
		T res = 0;
		
		while ( ind ){
			res += tree[ind];
			ind -= ind & -ind;
		}
		
		return res;
	}
};

template<typename T>
class Bit2D{
private:
	vector<Bit<T> >tree;
	int size;

public:
	Bit2D(int r, int c) : size(r + 1){
		tree.reserve(r + 1);
		for ( int i = 0 ; i <= r ; i++ ) tree.push_back(Bit<T>(c));
	}
	
	void add(int indx, int indy, T val){
		while ( indx < size ){
			tree[indx].add(indy, val);
			indx += indx & -indx;
		}
	}
	
	T sum(int indx, int indy){
		T res = 0;
		while ( indx ){
			res += tree[indx].sum(indy);
			indx -= indx & -indx;
		}
		
		return res;
	}
};

int main(){
	int N, M, ks = 0;
	
	ios::sync_with_stdio(true);
	while ( scanf("%d%d", &N, &M) == 2 ){
		Bit2D<ll> bit2d(N, N);
		
		for ( int i = 1 ; i <= N ; i++ )
			for ( int j = 1 ; j <= N ; j++ ){
				int x;
				scanf("%d", &x);
				bit2d.add(i, j, x);
			}

		if ( ks ) puts("");
		ks++;
		ll chcksum = 0;
		for ( int i = 1 ; i <= N - M + 1 ; i++ )
			for ( int j = 1 ; j <= N - M + 1 ; j++ ){
				int r = i + M - 1, c = j + M - 1;
				ll now = bit2d.sum(r,c) - bit2d.sum(r - M, c) - bit2d.sum(r, c - M) + bit2d.sum(r - M, c - M);
				chcksum += now;
				printf("%lld\n", now);
			}

		printf("%lld\n", chcksum);
	}
	
	return 0;
}

