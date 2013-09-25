#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

char first[12], second[12], pattern[5];
int T[6];
int turn = 1;
int vis[12][5][2][10][2];
int dp[12][5][2][10][2];

int rec(int pos, int patPos, int lss, int last, int nonZero){
	if ( first[pos] == 0 && pattern[patPos] == 0 ) return 1;
	if ( first[pos] == 0 ) return 0;
	if ( vis[pos][patPos][lss][last][nonZero] == turn ) return dp[pos][patPos][lss][last][nonZero];

	vis[pos][patPos][lss][last][nonZero] = turn;
	int temp = 0;

	for ( char i = '0' ; i <= '9' ; i++ ){
		int nlss = lss;
		int nNon = nonZero;
		if ( lss == 0 && i > first[pos] ) continue;
		if ( lss == 0 && i < first[pos] ) nlss = 1;

		if ( nonZero == 0 && i != '0' ) nNon = 1;
		if ( pattern[patPos] == 0 ) temp += rec(pos+1, patPos, nlss, i-'0', nNon);
		else if ( pattern[patPos] == i && nNon ) temp += rec(pos+1, patPos+1, nlss, i-'0', nNon);
		else if ( patPos && pattern[T[patPos]] == i && nNon) temp += rec(pos+1, T[patPos] + 1, nlss, i-'0', nNon);
		else temp += rec(pos+1, 0, nlss, i-'0', nNon);
	}

	return dp[pos][patPos][lss][last][nonZero] = temp;
}

int main(){
	int a, b, n;

	while ( cin >> a >> b >> n ){
		if ( a == b && b == n && n == -1 ) break;
		
		T[0] = -1;
		sprintf(pattern, "%d", n);
		
		for (int i=0; pattern[i] != '\0'; i++) {
			T[i+1] = T[i] + 1;
			while (T[i+1] > 0 && pattern[i] != pattern[T[i+1]-1])
				T[i+1] = T[T[i+1]-1] + 1;
		}

		sprintf(first, "%010d", b);
		int res = rec(0, 0, 0, 0, 0);
		turn++;
		
		sprintf(first, "%010d", a-1);
		if ( a == 0 && n == 0 ) res++;
		else if ( a ) res -= rec(0, 0, 0, 0, 0);
		
		cout<<res<<endl;
		turn++;
	}

	return 0;
}

