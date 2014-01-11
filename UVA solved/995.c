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

int b;
char isValid[10];
char number[55], largest[55];

int getMod(char *num, int len, int mod){
	int i, res = 0;
	
	/*printf("%s to be divided by %d\n", num, mod);*/
	for ( i = 0 ; i < len ; i++ ) res = ( b * res + num[i] - '0' ) % mod;
	return res;
}

void bkTk(int ind, int leading){
	int i, mod, div;

	for ( i = 0 ; i < 10 ; i++ ){
		if ( leading == 0 && i == 0 ) continue;
		if ( isValid[i] ){
			number[ind] = i + '0';
			if ( getMod(number, ind + 1, ind + 1) == 0 ) bkTk(ind + 1, 1);
			else{
				number[ind] = 0;
				if ( strlen(largest) <= ind ){
					strcpy(largest, number);
				}
			}
			number[ind] = 0;
		}
	}
}

int main(){
	int i;
	char arr[30];
	
	while ( scanf("%d%s", &b, arr) == 2 ){
		for ( i = 0 ; i < 10 ; i++ ) isValid[i] = 0;
		for ( i = 0 ; arr[i] ; i++ ) isValid[arr[i] - '0'] = 1;
		largest[0] = 0;
		bkTk(0, 0);
		puts(largest);
	}
	
	return 0;
}

