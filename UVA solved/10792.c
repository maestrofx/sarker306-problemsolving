#include<stdio.h>
#include<math.h>

int main(){
	double h1, h2, r, d;
	int test, i;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		scanf("%lf%lf%lf", &r, &d, &h1);
		h2=(1-cos(2*acos(1-d/r)-acos(1-h1/r)))*r;
		printf("Case %d: %.4lf\n", i, h2);
	}
	
	return 0;
}
