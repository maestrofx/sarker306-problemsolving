#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100005

void computeFailure(char *pattern, long *failure){
	long m = strlen(pattern), i, k = 0;
	
	failure[0] = failure[1] = 0;
	for ( i = 2 ; i <= m ; i++ ){
		while ( k > 0 && pattern[k] != pattern[i - 1] )
			k = failure[k];
		
		if ( pattern[k] == pattern[i - 1] )
			k++;
		
		failure[i] = k;
		/* printf("failure[%ld] = %ld\n", i, k); */
	}
}

void kmpMatcher(char *text, char *pattern, long *failure){
	long m = strlen(text), i, k = 0;
	
	computeFailure(pattern, failure);
	for ( i = 0 ; i < m ; i++ ){
		while ( k > 0  && pattern[k] != text[i-1] )
			k = failure[k];
		
		if ( pattern[k] == text[i-1] )
			k++;
	}
	
	for ( m = 0 ; m + k + 1 < i ; m++ ) putchar(text[m]);
	puts(pattern);
}

void strRev(char *to, char *from){
	long i, j = strlen(from);
	
	for ( i = 0, to[j] = 0; i < j ; i++ )
		to[i] = from[j - i - 1];
}

long fail[SIZE];
char input[SIZE], reved[SIZE];

int main(){
	while ( gets(input) ){
		strRev(reved, input);
		/*puts(reved);*/
		
		kmpMatcher(input, reved, fail);
	}
	
	return 0;
}
