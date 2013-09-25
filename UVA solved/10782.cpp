// 10782.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS  

#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int n;
char vals[128], lowLimit[128];
char isVar[128];
char isAvailable[10];
char addend[12][15], original[12][15];
char solnFound;

void cutePrint(){
	for ( int i = 0 ; i < n ; i++ ){
		int j;
		for ( j = 0 ; addend[i][j] ; j++ );
		for ( --j ; j >= 0 ; j-- ){
			if ( addend[i][j] == '0' ) putchar(' ');
			else putchar(vals[addend[i][j]] + '0');
		}

		puts("");
	}
}

void backtrack(int row, int col, int sumSoFar){
	if ( addend[row][col] == 0 ){
		if ( sumSoFar != 0 ) return;
		solnFound = 1;
		int atleastOnePrinted = 0;
		for ( int i = 'A' ; i <= 'Z' ; i++ ){
			if ( !isVar[i] ) continue;
			if ( atleastOnePrinted ) putchar(' ');
			printf("%c=%d", i, vals[i]);
			atleastOnePrinted = 1;
		}

		puts("");
#ifndef ONLINE_JUDGE
		cutePrint();
#endif
		return;
	}

	if ( solnFound == 0 ){
		if ( vals[addend[row][col]] == -1 ){
			if ( !isVar[addend[row][col]] ){
				backtrack(row + 1, col, sumSoFar);
				return;
			}
			else if ( row == n - 1 ){
				int sum = sumSoFar;
				int res = sum % 10;
				if ( res >= lowLimit[addend[row][col]] && isAvailable[res] == 1 ){
					isAvailable[res] = 0;
					vals[addend[row][col]] = res;
					backtrack(0, col + 1, sum / 10);
					isAvailable[res] = 1;
					vals[addend[row][col]] = -1;
				}

				return;
			}

			for ( int i = 9 ; i  >= lowLimit[addend[row][col]] ; i-- ){
				if ( isAvailable[i] == 0 ) continue;
				vals[addend[row][col]] = i;
				isAvailable[i] = 0;
				backtrack(row + 1, col, sumSoFar + i);
				isAvailable[i] = 1;
				vals[addend[row][col]] = -1;
			}
		}
		else {
			if ( row == n - 1 ){
				int sum = sumSoFar;
				int res = sum % 10;
				if ( res != vals[addend[row][col]] ) return;
				backtrack(0, col + 1, sum / 10);
			}
			else backtrack(row + 1, col, sumSoFar + vals[addend[row][col]]);
		}
	}
}

void assignValues(){
	memset(isVar, 0, sizeof(isVar));
	memset(vals, -1, sizeof(vals));
	memset(isAvailable, 1, sizeof(isAvailable));
	memset(lowLimit, 0, sizeof(lowLimit));

	solnFound = 0;
	for ( int i = 0 ; i < n ; i++ ){
		int j;
		for ( j = 0 ; addend[i][j] ; j++ ){
			if ( isalpha(addend[i][j]) && !isVar[addend[i][j]] ) isVar[addend[i][j]] = 1;
		}
	}
	
	for ( int j = 0 ; addend[n-1][j] ; j++ ){ /// for this problem, only the summation contained no leading zero
		if ( isalpha(addend[n-1][j]) && !isVar[addend[n-1][j+1]]) lowLimit[addend[n-1][j]] = 1;
	}
	backtrack(0, 0, 0);
}

int main()
{
	int test;

	while ( scanf("%d", &test) == 1 ){
		for ( int ks = 1 ; ks <= test ; ks++ ){
			scanf("%d", &n);
			int mxlen = 0;
			for ( int i = 0 ; i < n ; i++ ){
				memset(addend[i], 0, sizeof(addend[i]));
				scanf("%s", addend[i]);
				strcpy(original[i], addend[i]);
				int tmplen = strlen(addend[i]);
				if ( mxlen < tmplen ) mxlen = tmplen;
				reverse(addend[i], addend[i] + tmplen);
			}

			for ( int i = 0 ; i < n ; i++ ){
				int j;
				for ( j = 0 ; addend[i][j] ; j++ );
				for ( ; j < mxlen ; j++ ) addend[i][j] = '0';
				addend[i][j] = 0;
				//printf("%s\n", addend[i]);
			}

			assignValues();
		}
	}

	return 0;
}
