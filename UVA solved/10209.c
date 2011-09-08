#include<stdio.h>

#define R1 0.315146743627720512
#define R2 0.511299166334352064
#define R3 0.173554090037927392

int main(){
	double a, x;
	
	while(scanf("%lf", &a)!=EOF){
		x=a*a;
		printf("%.3lf %.3lf %.3lf\n", R1*x, R2*x, R3*x);
	}
	
	return 0;
}
