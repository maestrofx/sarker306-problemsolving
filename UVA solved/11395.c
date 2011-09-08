#include<stdio.h>
#include<math.h>

int main(){
	long long n;
	
	while(scanf("%I64d",&n)==1&&n){
		printf("%I64d\n",n-(long long) sqrt(n)-(long long ) sqrt(n/2.0));
	}
	return 0;
}
