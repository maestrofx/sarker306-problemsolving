#include <stdio.h>
#include <string.h>

typedef long long unsigned llu;
int visited[17][17][17], True = 1, n;
llu dp[17][17][17];
char conf[18], val[128];

llu rec(int col, int row, int last){
	llu res = 0;
	
	if ( col == n ) return 1;
	if ( row == n ) return 0;
	if ( visited[col][row][last] == True ) return dp[col][row][last];
	
	visited[col][row][last] = True;
	if ( abs(row - last) > 1 ){
		if ( conf[col] == '?' ) res += rec(col + 1, 0, row);
		else if ( val[conf[col]] - 1 == row ) res += rec(col + 1, 0, row);
	}
	
 	res += rec(col, row + 1, last);
	
	return dp[col][row][last] = res;
}

llu solve(){
	llu res = 0;
	int i;
	
	for ( i = 0 ; conf[i] ; i++ ){
		if ( conf[i] != '?' && val[conf[i]] > n ) return 0;
	}
	
	if ( conf[0] == '?' ){
		for ( i = 0 ; i < n ; i++ ) res += rec(1, 0, i);
	}
	else res = rec(1, 0, val[conf[0]] - 1);
	
	return res;
}

int main(){
    int i;

    for(i = 0 ; i < 10 ; i++ ) val[i + '0'] = i;
    for( i = 0 ; i < 6 ; i++ ) val[i + 'A'] = i + 10;
    while(scanf("%s", conf) == 1){
    	for ( n = 0 ; conf[n] && conf[n] != ' ' ; n++ );
        printf("%llu\n", solve());
        True++;
    }

    return 0;
}

