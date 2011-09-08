#include<stdio.h>

int main(){
	long long m, n, x;
	
	while(scanf("%I64d%I64d", &m, &n)!=EOF){
		if(m==0 && n==0) break;
		if(m>n) m^=n^=m^=n;
		x=m*(m-1);
		x=m*n*(m+n-2)+2*x*(n-m+1)+2*(x*(2*m-1))/3-2*x;
		printf("%I64d\n", x);
	}
	
	return 0;
}
