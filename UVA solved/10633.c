#include<stdio.h>

int main(){
	long long unsigned x, y;
	
	while(scanf("%I64u", &x)!=EOF){
		if(x==0) break;
		
		if(x%9){
			y=(10*x)/9;
			printf("%I64u\n", y);
		}
		else{
			y=x/9;
			printf("%I64u %I64u\n", 10*y-1, 10*y);
		}
	}
	
	return 0;
}
