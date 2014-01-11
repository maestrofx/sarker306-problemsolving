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

int n, m;
int flag;
char number[55];
char cache[31][31][35];

int getMod(char *num, int len, int mod){
	int i, res = 0;

	/*printf("%s to be divided by %d\n", num, mod);*/
	for ( i = 0 ; i < len ; i++ ) res = ( 10 * res + num[i] - '0' ) % mod;
	return res;
}

void bkTk(int ind, int leading){
	int i, mod, div;

	if ( ind == m ){
		number[ind] = 0;
		strcpy(cache[n][m], number);
		flag = 1;
	}
	
	for ( i = 0 ; i < 10 && flag == 0 ; i++ ){
		if ( leading == 0 && i == 0 ) continue;
		number[ind] = i + '0';
		
		if ( ind + 1 >= n && getMod(number, ind + 1, ind + 1) == 0 ) bkTk(ind + 1, 1);
		else if ( ind + 1 < n ) bkTk(ind + 1, 1);
		number[ind] = 0;
	}
}

void findNumber(){
	if ( cache[n][m][0] == 0 ){
		flag = 0;
		bkTk(0,0);
		if ( flag == 0 ) strcpy(cache[n][m], "-1");
	}
	
	puts(cache[n][m]);
}

int main(){
	int test, ks;
	char arr[30];

	while ( scanf("%d", &test) == 1 ){
		for ( ks = 1 ; ks <= test ; ks++ ){
			scanf("%d%d", &n, &m);
			printf("Case %d: ", ks);
			findNumber();
		}
	}

	return 0;
}

