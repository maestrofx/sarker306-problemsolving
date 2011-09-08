#include<stdio.h>
#include<math.h>

#define EPS 1e-3
#define INF 1000000000

typedef struct{
	double x, y;
}point;

typedef struct{
	double a, b, c;
}line;

typedef struct{
	double r, g, f, c;
	point o;
}circle;

double distance(point a, point b){
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

int comp(point a, point b){
	if(a.x==b.x || (a.x-b.x>-EPS && a.x-b.x<EPS)){
		if(a.y==b.y || (a.y-b.y>-EPS && a.y-b.y<EPS)) return 0;
		if(a.y>b.y) return 1;
		return -1;
	}
	else if(a.x>b.x) return 1;
	return -1;
}

void setcircle(circle *p){
	p->g=-p->o.x, p->f=-p->o.y;
	p->c=p->g * p->g + p->f * p->f - p->r * p->r;
}

void setline(line *p, double a, double b, double c){
	p->a=a, p->b=b, p->c=c;
}

void parallelline(line *p, line q, double dis){
	p->a=q.a, p->b=q.b, p->c=q.c+dis;
}

point solve(line p, line q){
	point s;
	double det=p.a*q.b-p.b*q.a;
	
	s.x=INF, s.y=INF;
	if(det==0 || (det>-EPS && det<EPS)) return s;
	s.x=(p.b*q.c-p.c*q.b)/det;
	s.y=(p.c*q.a-p.a*q.c)/det;
	return s;
}

int main(){
	circle a, b, temp;
	line m, n, x, y;
	point p, p1, p2;
	double dif, hu, bu;
	
	while(scanf("%lf%lf%lf%lf%lf%lf", &a.o.x, &a.o.y, &a.r, &b.o.x, &b.o.y, &b.r)!=EOF){
		setcircle(&a);
		setcircle(&b);
		if(a.r<b.r){
			temp=a;
			a=b;
			b=temp;
		}
		
		dif=distance(a.o, b.o);
		if(dif>-EPS && dif<EPS){
			if(a.r>-EPS && a.r<EPS && b.r>-EPS && b.r<EPS){
				if(a.o.x>-EPS && a.o.x<EPS) a.o.x=0.0;
				if(a.o.y>-EPS && a.o.y<EPS) a.o.y=0.0;
				printf("(%.3lf,%.3lf)\n", a.o.x, a.o.y);
			}
			else if(a.o.x-b.o.x>-EPS && a.o.x-b.o.x<EPS && a.o.y-b.o.y>-EPS && a.o.y-b.o.y<EPS && a.r-b.r>-EPS && a.r-b.r<EPS){	
				printf("THE CIRCLES ARE THE SAME\n");
			}
			else printf("NO INTERSECTION\n");
		}
		else if(dif==a.r+b.r || (dif-a.r-b.r<EPS && dif-a.r-b.r>-EPS)){
			hu=(a.r*b.o.x+b.r*a.o.x)/(a.r+b.r), bu=(a.r*b.o.y+b.r*a.o.y)/(a.r+b.r);
			if(hu>-EPS && hu<EPS) hu=0.0;
			if(bu>-EPS && bu<EPS) bu=0.0;
			printf("(%.3lf,%.3lf)\n", hu, bu);
		}
		else if(dif>a.r+b.r){
			printf("NO INTERSECTION\n");
		}
		else if(dif==a.r-b.r ||(dif-a.r+b.r>-EPS && dif-a.r+b.r<EPS)){
			hu=(a.r*b.o.x-b.r*a.o.x)/(a.r-b.r), bu=(a.r*b.o.y-b.r*a.o.y)/(a.r-b.r);
			if(hu>-EPS && hu<EPS) hu=0.0;
			if(bu>-EPS && bu<EPS) bu=0.0;
			printf("(%.3lf,%.3lf)\n", hu, bu);
		}
		else if(dif<a.r+b.r && dif>a.r-b.r){
			bu=(a.r*a.r-b.r*b.r)/(2*dif)+dif/2;
			hu=sqrt(a.r*a.r-bu*bu);
			setline(&m, 2*(a.g-b.g), 2*(a.f-b.f), a.c-b.c);
			setline(&n, b.f-a.f, a.g-b.g, a.g*b.f-a.f*b.g);
			parallelline(&x, n, hu*sqrt(n.a*n.a+n.b*n.b));
			p1=solve(x,m);
			parallelline(&x, n, -hu*sqrt(n.a*n.a+n.b*n.b));
			p2=solve(x,m);
			if(p1.x>-EPS && p1.x<EPS) p1.x=0.0;
			if(p2.x>-EPS && p2.x<EPS) p2.x=0.0;
			if(p1.y>-EPS && p1.y<EPS) p1.y=0.0;
			if(p2.y>-EPS && p2.y<EPS) p2.y=0.0;
			if(comp(p1, p2)>0){
				p=p1;
				p1=p2;
				p2=p;
			}
			printf("(%.3lf,%.3lf)", p1.x, p1.y);
			printf("(%.3lf,%.3lf)\n", p2.x, p2.y);
		}
		else printf("NO INTERSECTION\n");
	}
	
	return 0;
} /* -9.0 7.2 3.6
5.6 7.2 18.2 */
