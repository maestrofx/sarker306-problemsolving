#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000005

char input[SIZE], temp[SIZE<<1];
long failure[SIZE];

void computeFailure( long *fail, char *pattern ){
	long i, j, q, k, patternLen = strlen(pattern);
	
	/* fail[x] is the order of the longest proper prefix of xth prefix
	   that is also a suffix of it. 0th prefix is "" */
	fail[0] = fail[1] = 0;

	for ( q = 2 ; q <= patternLen ; q++ ){
		k = fail[q - 1];
		
		for ( ; ; k = fail[k] ){
			if ( pattern[k] == pattern[ q - 1 ] ){
				fail[q] = k + 1;
				break;
			}
			if ( k == 0 ) {
				fail [ q ] = 0;
				break;
			}
		}
		
		/*printf("fail[%d] = %d\n", q, fail[q]);*/
	}
}

long powerOfString( long *fail, char *txt, char *pattern ){
	long m = strlen(pattern), n, i, j;
	
	n = m<<1;
	computeFailure(fail, pattern);
	strcpy(txt, pattern);
	strcat(txt, pattern);
	
	i = 0;  /* the initial state of the automaton is
              the empty string */

	j = 1; 	/*  the first character of the text ... if j == 0 already match, we will 
				find next match */
  
	for( ; ; ) {
		if(j == n) break; /* we reached the end of the text */

/* 		if the current character of the text "expands" the
		current match  */
		if(txt[j] == pattern[i]) {
			i++; /* change the state of the automaton */
			j++; /* get the next character from the text */
			if(i == m){
				/*printf("Position %d of text, position %d of pattern\n", j, i);*/
				return m /( j - i ); /* match found */
			}
		}

/* 		if the current state is not zero (we have not
		reached the empty string yet) we try to
		"expand" the next best (largest) match */
		else if(i > 0) i = fail[i];

/* 		if we reached the empty string and failed to
		"expand" even it; we go to the next 
		character from the text, the state of the
		automaton remains zero */
		else j++;
	}
}

int main(){
	while ( gets(input) ){
		if ( input[0] == '.' && input[1] == 0 ) break;
		printf("%ld\n", powerOfString(failure, temp, input));
	}
	
	return 0;
}
