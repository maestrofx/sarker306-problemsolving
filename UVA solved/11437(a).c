#include<stdio.h>
#include<math.h>

typedef struct{
	double x, y;
}point;

typedef struct{
	point p1, p2, p3;
	double area;
}triangle;

void settriangle(triangle *p, point a, point b, point c){
	p->p1=a, p->p2=b, p->p3=c;
	p->area=0.5*((a.x-c.x)*(b.y-a.y)-(a.x-b.x)*(c.y-a.y)); /* area of triangle */
	if(p->area<0) p->area=-p->area;
}

int main(){
	long test;
	point a, b, c;
	triangle t1;
	
	scanf("%ld", &test);
	while(test--){
		scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
		settriangle(&t1, a, b, c);
		printf("%ld\n", (long)(t1.area/7+0.5));
	} 
	
	return 0;	
}
