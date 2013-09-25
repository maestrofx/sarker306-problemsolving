// 565.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS  
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>

#define MXCLAUSE 15

char truth[128], isVar[128], dual[128];
char clauses[MXCLAUSE][27], isTrueClause[MXCLAUSE];
int cntClause;
char isSatisfied;

void printClauses(){
	for ( int i = 0 ; i < cntClause ; i++ ) puts(clauses[i]);
}

int findUnit(){
	return 0;
}

int findPureLiteral(){
	char form[26], flag = 0;

	memset(form, 0, sizeof(form));
	for ( int i = 0 ; i < cntClause ; i++ ){
		if ( isTrueClause[i] ) continue;
		for ( int j = 'A' ; j <= 'P' ; j++ )
			if ( clauses[i][j - 'A'] != ' ' && form[j - 'A'] && form[j - 'A'] != clauses[i][j - 'A']) form[j - 'A'] = -1;
			else if ( form[j - 'A'] == 0 && clauses[i][j-'A'] != ' ' ) form[j - 'A'] = clauses[i][j - 'A'];
	}

	for ( int i = 0 ; i < cntClause ; i++ ){
		if ( isTrueClause[i] ) continue;
		for ( int j = 'A' ; j <= 'P' ; j++ ){
			if ( form[j - 'A'] > 0 && clauses[i][j - 'A'] == form[j - 'A']){
				truth[j] = ( form[j - 'A'] == j ) ? 1 : 0;
				truth[dual[j]] = truth[j] ^ 1;

				isTrueClause[i] = 1;
				flag = 1;
			}
		}
	}

	return flag;
}

void backtrack(){
	int flag = 1;

	for ( int i = 0 ; i < cntClause ; i++ ){
		if ( isTrueClause[i] == 0 ){
			flag = 0; break;
		}
	}

	if ( flag == 1 ){
		isSatisfied = 1;
		return;
	}

	for ( int i = 0 ; i < cntClause ; i++ ){
		int cntUnassigned = 0;
		char unassigned = 0;
		if ( isTrueClause[i] ) continue;
		for ( int j = 'A' ; j <= 'P' ; j++ ){
			if ( clauses[i][j - 'A'] != ' ' && truth[clauses[i][j - 'A']] == -1 ) cntUnassigned++, unassigned = clauses[i][j - 'A'];
		}

		if ( cntUnassigned == 1 ){
			truth[unassigned] = 1;
			truth[dual[unassigned]] = 0;
		//	printf("%c assigned for clause %d\n", unassigned, i);
			isTrueClause[i] = 1;
			backtrack();
			if ( isSatisfied ) break;
		//	printf("%c unassigned for clause %d\n", unassigned, i);
		}
	}
	
	if ( isSatisfied ) return;
	
	int nextFalseClause = 0;
	for ( ; nextFalseClause < cntClause ; nextFalseClause++ )
		if ( isTrueClause[nextFalseClause] == 0 ) break;

	for ( int j = 'A' ; j <= 'P' ; j++ ){
		if ( truth[j] == -1 && clauses[nextFalseClause][j - 'A'] != ' ' ){
			char nxt = clauses[nextFalseClause][j - 'A'];
			truth[nxt] = 1;
			truth[dual[nxt]] = 0;
			//printf("->%c assigned true for clause %d\n", nxt, nextFalseClause);
			isTrueClause[nextFalseClause] = 1;
			backtrack();
			if ( isSatisfied ) break;
			truth[nxt] = 0;
			truth[dual[nxt]] = 1;
			isTrueClause[nextFalseClause] = 0;
			//printf("->%c assigned false for clause %d\n", nxt, nextFalseClause);
			backtrack();
			if ( isSatisfied ) break;
		}
	}
}

void findSatisfiableAssignment(){
	isSatisfied = 0;

	while ( findPureLiteral() );
	//for ( int i = 0 ; i < cntClause ; i++ ) printf("%d", isTrueClause[i]);
	//puts("");
	backtrack();

	if ( isSatisfied == 1 ){
		printf("Toppings: ");
		for ( int i = 'A' ; i <= 'P' ; i++ ) if ( truth[i] > 0 ) putchar(i);
		puts("");
	}
	else puts("No pizza can satisfy these requests.");

	return;
}

int main(int argc, char* argv[]) {
	char input[1000];
	
	memset(truth, -1, sizeof(truth));
	for ( int i = 0 ; i < MXCLAUSE ; i++ ) for ( int j = 0 ; j < 20 ; j++ ) clauses[i][j] = ' ';
	for ( int i = 'A' ; i <= 'P' ; i++ ) dual[i] = i - 'A' + 'a';
	for ( int i = 'a' ; i <= 'p' ; i++ ) dual[i] = i - 'a' + 'A';

	while ( gets(input) ){
		if ( input[0] == '.' ){
		//	printClauses();
			findSatisfiableAssignment();
			// lagaya la

			memset(truth, -1, sizeof(truth));
			memset(isVar, 0, sizeof(isVar));
			memset(isTrueClause, 0, sizeof(isTrueClause));
			cntClause = 0;
			for ( int i = 0 ; i < MXCLAUSE ; i++ )
				for ( int j = 0 ; j < 20 ; j++ ) clauses[i][j] = ' ';
		}
		else {
			for ( int i = 0 ; input[i] ; i++ ){
				if ( input[i] == '+' || input[i] == '-' ){
					char sgn = input[i];
					for ( ; !isalpha(input[i]) ; i++ );
					if ( sgn == '+' ) clauses[cntClause][input[i] - 'A'] = input[i];
					else clauses[cntClause][input[i] - 'A'] = input[i] + 'a' - 'A';
					isVar[input[i]] = 1;
				}
			}

			cntClause++;
		}
	}

	return 0;
}

