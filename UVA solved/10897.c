#include<stdio.h>
#include<math.h>

#define RADIUS 6371.01
#define PI 3.1415926535897932384626433832795

double greatcircledistance(double lat1, double long1, double lat2, double long2){
	double dellat=lat2-lat1, dellong=long2-long1;
	double x=cos(lat2)*sin(dellong);
	double y=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(dellong);
	double z=sin(lat1)*sin(lat2)+cos(lat1)*cos(lat2)*cos(dellong);
	
	x=x*x;
	y=y*y;
	return RADIUS*atan2(sqrt(x+y),z);
}

double greatcircledistance1(double lat1, double long1, double lat2, double long2){
	double dellat=lat2-lat1, dellong=long2-long1;
	double xx=sin(dellat/2), yy=sin(dellong/2);
	return 2*RADIUS*asin(sqrt(xx*xx+cos(lat1)*cos(lat2)*yy*yy));
}

double degtorad(double degree){
	double rad=degree*PI/180;
	return rad;
}

int main(){
	char p[5];
	double a, b, c, m, n, m1, n1;
	int test;
	
	scanf("%d", &test);
	while(test--){
		scanf("%lf%lf%lf%s", &a, &b, &c, p);
		m=degtorad(a+b/60+c/3600);
		if(p[0]=='S') m=-m;
		scanf("%lf%lf%lf%s", &a, &b, &c, p);
		n=degtorad(a+b/60+c/3600);
		if(p[0]=='W') n=-n;
		scanf("%lf%lf%lf%s", &a, &b, &c, p);
		m1=degtorad(a+b/60+c/3600);
		if(p[0]=='S') m1=-m1;
		scanf("%lf%lf%lf%s", &a, &b, &c, p);
		n1=degtorad(a+b/60+c/3600);
		if(p[0]=='W') n1=-n1;
		/*printf("%.2lf\n", greatcircledistance(m, n, m1, n1));*/
		printf("%.2lf\n", greatcircledistance1(m, n, m1, n1));
	}
	
	return 0;
}
