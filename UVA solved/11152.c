#include<stdio.h>
#include<math.h>

#define PI 3.1415926535897932384626433832795

double a, b, c, s, R, r, del, area_circumcircle, area_incircle;

int main(){
	while(scanf("%lf%lf%lf", &a, &b, &c)!=EOF){
		s=(a+b+c)/2;
		del=sqrt(s*(s-a)*(s-b)*(s-c));
		r=del/s;
		area_incircle=PI*r*r;
		R=(a*b*c)/(del*4);
		area_circumcircle=PI*R*R;
		printf("%.4lf %.4lf %.4lf\n", area_circumcircle-del, del-area_incircle, area_incircle); 
	}
	
	return 0;
}
