#include<stdio.h>

int main(){
	int test;
	long m, n;
	
	scanf("%d", &test);
	while(test--){
		scanf("%ld%ld", &m, &n);
		printf("%ld\n", (m/3) * (n/3));
	}
	
	return 0;
}
