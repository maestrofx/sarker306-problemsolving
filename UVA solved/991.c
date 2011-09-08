#include<stdio.h>

long a[]={1, 2, 5, 14, 42, 132, 429, 1430, 4862, 16796, 58786};

int main(){
	int n;
	
	scanf("%d", &n);
	printf("%ld\n", a[n-1]);
	while(scanf("%d", &n)!=EOF){
		if(n<1 && n>10) break;
		printf("\n%ld\n", a[n-1]);
	}
	
	return 0;
}
