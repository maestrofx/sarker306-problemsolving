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

char inp[400005], rev[200005];
long fail[200005];

int main(){
	long len, i, j, k, m, mCnt;
	int isPalin, test;
	
	scanf("%d", &test);
	while ( test-- ){
		scanf("%s", inp + 1);
		len = strlen(inp + 1);
		for ( i = 1, j = len ; i <= len ; i++, j-- ) rev[i] = inp[j];
		rev[i] = 0;
		
		for ( i = 1; i <= len ; i++ ) inp[len + i] = inp[i];
		inp[2 * len + 1] = 0;
		
		fail[0] = fail[1] = 0;
		k = 0;
		for ( i = 2 ; i <= len ; i++ ){
			while ( k > 0 && rev[k + 1] != rev[i] ) k = fail[k];
			if ( rev[k + 1] == rev[i] ) k++;
			fail[i] = k;
		}
		
		isPalin = 0;
		m = 0;
		mCnt = 0;
		for ( i = 1 ; i < 2 * len ; i++ ){
			while ( m > 0 && rev[m + 1] != inp[i] ) m = fail[m];
			if ( rev[m + 1] == inp[i] ) m++;
			if ( m == len ){
				if ( i - len == 0 ) isPalin = 1;
				else mCnt++;
			}
		}
		
		if ( mCnt ) puts("alindrome");
		else if ( isPalin ) puts("palindrome");
		else puts("simple");
	}
	
	return 0;
}

