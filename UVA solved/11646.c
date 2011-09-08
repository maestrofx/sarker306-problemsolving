#include<stdio.h>
#include<math.h>

int main(){
	int a, b, i=1;
	double x, costheta, r, theta, L, W;
	
	while(scanf("%d%*s%d", &a, &b)!=EOF){
		x=b/(a*1.0);
		theta=atan(x);
		costheta=cos(theta);
		r=100/(theta+costheta);
		L=2*r*costheta, W=L*x;
		printf("Case %d: %.10lf %.10lf\n", i++, L, W);
	}
	
	return 0;
}
