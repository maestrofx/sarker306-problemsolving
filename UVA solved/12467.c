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

char pat[1000003], str[1000003];
long fail[1000003];

void failure(char *pattern, long *f){ /* WARNING : 1-indexed */
	long i, k;

	f[0] = f[1] = 0;
	k = 0;
	for ( i = 2 ; pattern[i] ; i++ ){
		while ( k > 0 && pattern[k+1] != pattern[i] ) k = f[k];
		if ( pattern[k+1] == pattern[i] ) k++;
		f[i] = k;
	}
}

int main(){
	int test, ks;
	long i, j, len, m, maxM, maxMInd;
	
	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%s", pat + 1);
			
			len = strlen(pat + 1);
			for ( i = 1, j = len ; i <= len ; i++, j-- ) str[i] = pat[j];
			str[i] = 0;
			
			failure(pat, fail);
			m = 0;
			maxM = 0, maxMInd = -1;
			for ( i = 1 ; i <= len ; i++ ){
				while ( m > 0 && pat[m + 1] != str[i] ) m = fail[m];
				if ( pat[m + 1] == str[i] ) m++;
				if ( m > maxM ) maxM = m, maxMInd = i;
			}
			
			for ( i = maxM ; i ; i-- ) putchar(pat[i]);
			puts("");
		}
	}

	return 0;
}

