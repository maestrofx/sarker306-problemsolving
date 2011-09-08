#include<stdio.h>
#define EPS 1e-6

typedef struct _point{
	double x, y;
}point;

int compare(point a, point b){
	double delx=a.x-b.x, dely=a.y-b.y;
	
	if(delx<EPS && delx>-EPS && dely<EPS && dely>-EPS) return 0;
	return 1;
}

int main(){
	point a, b, c, d;
	
	while(scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y, &d.x, &d.y)==8){
		if(compare(a, c)==0) printf("%.3lf %.3lf\n", b.x+d.x-a.x, b.y+d.y-a.y);
		else if(compare(a, d)==0) printf("%.3lf %.3lf\n", b.x+c.x-a.x, b.y+c.y-a.y);
		else if(compare(b, d)==0) printf("%.3lf %.3lf\n", a.x+c.x-b.x, a.y+c.y-b.y);
		else if(compare(b, c)==0) printf("%.3lf %.3lf\n", a.x+d.x-b.x, a.y+d.y-b.y);
	}
	
	return 0;
}
