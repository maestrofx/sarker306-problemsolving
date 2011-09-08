#include<stdio.h>
#include<math.h>
#include<stdlib.h>

#define EPS 0.000000001

int main(){
	double area, r, a, PI=2*acos(0);
	int n, test=1;
	
	while(scanf("%d%lf", &n, &area)!=EOF && n>2){
		printf("Case %d:", test++);
		r=2*PI*area/(n*sin(2*PI/n))-area;
		printf(" %.5lf", r);
		r=area-PI*area/(n*tan(PI/n));
		printf(" %.5lf\n", r);
	}
	
    return 0;
}
