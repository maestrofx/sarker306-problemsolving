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
#define SIZE 2002
char arr[SIZE][2][500];
char cum[SIZE][500];
char dp[SIZE][500];
int mtch[] = {6,2,5,5,4,5,6,3,7,6};
int cache[] = {0,1,2,4,9,16};

void bigRevAdd(char *to, char *one, char *two){ /* reverse add */
	int i, j, carry = 0, sum;
	char temp[500];
	
	for ( i = 0 ; one[i] && two[i] ; i++ ){
		sum = carry + one[i] + two[i] - 96;
		carry = sum / 10;
		sum %= 10;
		temp[i] = sum + '0';
	}
	
	if ( one[i] ){
		for ( ; one[i] ; i++ ){
			sum = carry + one[i] - 48;
			carry = sum / 10;
			sum %= 10;
			temp[i] = sum + '0';
		}
	}
	else{
		for ( ; two[i] ; i++ ){
			sum = carry + two[i] - 48;
			carry = sum / 10;
			sum %= 10;
			temp[i] = sum + '0';
		}
	}
	
	while ( carry ){
		temp[i++] = carry % 10 + '0';
		carry /= 10;
	}
	temp[i] = 0;
	strcpy(to, temp);
}

int main(){
	int i, j, n;
	
	arr[0][0][0] = '0', arr[0][1][0] = '1';
	dp[0][0] = '1';
	cum[0][0] = '1';
	
	for ( i = 1 ; i < SIZE ; i++ ){
		strcpy(arr[i][1], "0");
		
		for ( j = 1 ; j < 10 ; j++ )
			if ( i >= mtch[j] ) bigRevAdd(arr[i][1], arr[i][1], dp[i-mtch[j]]);
			
		if ( i >= mtch[0] ) strcpy(arr[i][0], dp[i-mtch[0]]);
		
		bigRevAdd(dp[i], arr[i][1], arr[i][0]);
		bigRevAdd(cum[i], cum[i - 1], arr[i][1]);
	}
	
	while ( scanf("%d", &n) == 1 ){
		if ( n <= 6 ) printf("%d", cache[n - 1]);
		else for ( i = strlen(cum[n]) - 1 ; i >= 0 ; i-- ) putchar(cum[n][i]);
		puts("");
	}
	
	return 0;
}

