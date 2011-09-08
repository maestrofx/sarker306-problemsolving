#include<stdio.h>
#include<math.h>

#define PI 3.1415926535897932384626433832795
#define RADIUS 6440

int main(){
	char a[10];
	double s, angle, r;
	
	while(scanf("%lf%lf%s", &s, &angle, a)!=EOF){
		if(a[0]=='m') angle/=60;
		if(angle>180) angle=360-angle;
		angle=angle*PI/180;
		r=s+RADIUS;
		printf("%lf %lf\n", r*angle, r*sqrt(2*(1-cos(angle))));
	}
	
	return 0;
}
