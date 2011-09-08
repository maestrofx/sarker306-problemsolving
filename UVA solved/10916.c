#include<stdio.h>
#include<math.h>

typedef long long llong;
llong array[30]={3,5,8,12,20,34,57,98,170,300,536,966,1754,3210,5910,10944,20366,38064,71421,134480,254016};

int main(){
	llong y, n;
	double x;
	
	while(scanf("%lld", &y)!=EOF && y){
		y=(llong)(y/10-194);
		/*for(n=2, x=pow(2,y)*log(2);x>0;n++) x-=log(n);
		printf("%lld\n", n-2);*/
		printf("%lld\n", array[y-2]);
	}
	
	return 0;
}
