#include <stdio.h>

#define SIZE 4194305
char cache[SIZE];

char moliu( unsigned int n ){
	char res, tmp;
	
	if ( n < SIZE && cache[n] ) return cache[n];
	if ( n == 0 ) return 0;
	
	if ( n & 1 ){
		res = moliu(n-1) + 1;
		tmp = moliu(n+1) + 1;
		if ( tmp < res ) res = tmp;
	}
	else res = moliu(n>>1) + 1;
	
	if ( n < SIZE ) cache[n] = res;
	return res;
}

int main(){
	unsigned int n;
	
	cache[1] = 1;
	cache[2] = 2;
	cache[4] = 3;
	cache[3] = 3;
	
	while ( scanf("%d", &n) == 1 ) printf("%d\n", moliu(n));
	
	return 0;
}
