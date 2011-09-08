#include<stdio.h>
#include<math.h>

#define INF -99999999.0
#define EPS 1e-6

typedef struct{
	double x, y;
}point;

typedef struct{
	double a, b, c;
}line;

typedef struct{
	point p1, p2, p3;
	double area;
}triangle;

double _abs(double x){
	if(x>-EPS && x<EPS) return 0;
	if(x<0) return -x;
	else return x;	
}

void settriangle(triangle *p, point a, point b, point c){
	p->p1=a, p->p2=b, p->p3=c;
	p->area=0.5*((a.x-c.x)*(b.y-a.y)-(a.x-b.x)*(c.y-a.y)); /* area of triangle */
	if(p->area<0) p->area=-p->area;
}

void solveline(point *p, line l1, line l2){
	double det=l1.a*l2.b-l1.b*l2.a;
	if(_abs(det)==0.0) p->x=INF, p->y=INF;
	else{
		p->x=(l1.b*l2.c-l1.c*l2.b)/det, p->y=(l1.c*l2.a-l1.a*l2.c)/det;
	}
}

void setline(line *p, point a, point b){
	p->a=a.y-b.y, p->b=b.x-a.x, p->c=a.x*b.y-a.y*b.x;	
}

void ratio_intersect_point(point *p, point a, point b, double m, double n){
	if(m+n==0) p->x=INF, p->y=INF;
	else p->x=(a.x*n+b.x*m)/(m+n), p->y=(a.y*n+b.y*m)/(m+n);
}

int main(){
	long test;
	point a, b, c;
	point d, e, f, p, q, r;
	line l1, l2, l3;
	triangle t1, t2;
	
	scanf("%ld", &test);
	while(test--){
		scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
		settriangle(&t1, a, b, c);
		ratio_intersect_point(&d, b, c, 1, 2);
		ratio_intersect_point(&e, c, a, 1, 2);
		ratio_intersect_point(&f, a, b, 1, 2);
		setline(&l1, a, d);
		setline(&l2, b, e);
		setline(&l3, c, f);
		solveline(&p, l1, l2);
		solveline(&q, l2, l3);
		solveline(&r, l3, l1);
		settriangle(&t2, p, q, r);
		printf("%ld\n", (long)(t2.area+0.5));
	} 
	
	return 0;	
}
