#include<stdio.h>
#include<math.h>

int main(){
	int test, a, b, c, d, i;
	int p, q, r;
	double x;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		scanf("%d%d%d%d", &a, &b, &c, &d);
		p=2*(a-b);
		q=4*b;
		r=-a-b;
		x=1-(-q+sqrt(q*q-4*p*r))/(2.0*p);
		printf("Land #%d: %.6lf %.6lf\n", i, c*x, d*x);
	}
	
	return 0;
}
