#include<stdio.h>
#include<math.h>

#define PI 3.1415926535897932384626433832795

int main(){
	double L, D, b;
	int test;
	
	scanf("%d", &test);
	while(test--){
		scanf("%lf%lf", &D, &L);
		b=sqrt(L*L-D*D)/4;
		printf("%.3lf\n", PI*L*b);
	}
	
	return 0;
}
