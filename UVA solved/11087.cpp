#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include <stdlib.h>
#include <map>

typedef long long ll;
using namespace std;

int main(int argc, char* argv[]){
	int test, ks, n, k, mods[502];
	ll result;
	map<int, int>::iterator ptr;

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ;ks++ ){
			int x;
			map<int, int> freq;

			result = 0;
			scanf("%d%d", &n, &k);
			for ( int i = 0 ; i < n ; i++ ){
				scanf("%d", &x);
				ptr = freq.find(x);
				if ( ptr != freq.end() ) ptr->second++;
				else freq.insert(pair<int, int>(x, 1));
			}

			for ( int i = 0 ; i < k ; i++ ) mods[i] = 0;
			for ( ptr = freq.begin() ; ptr != freq.end() ; ptr++ ){
				x = ptr->first;
				int md = ( k + x % k) % k;
				if ( ptr->second > 1 && (x*2)%k == 0 ) result++;
				result += mods[(k-md)%k];
				mods[md]++;
			}

			printf("Case %d: %lld\n", ks, result);
		}
	}

	return 0;
}
