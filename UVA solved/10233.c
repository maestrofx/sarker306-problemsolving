#include<stdio.h>
#include<math.h>

#define HUU sqrt(3)/6

typedef long xx;

double triangle_lattice_distance(xx a, xx b){
	double x1, x2, y1, y2;
	xx m, p, q;
	
	m=sqrt(a);
	p=a-m*m;
	q=(p+1)/2;
	x1=m+(1-q)*0.5;
	q=p/2;
	y1=HUU;
	if(p%2==0) y1=y1+3*q*HUU;
	else y1=y1+(3*q+1)*HUU;
	m=sqrt(b);
	p=b-m*m;
	q=(p+1)/2;
	x2=m+(1-q)*0.5;
	q=p/2;
	y2=HUU;
	if(p%2==0) y2=y2+3*q*HUU;
	else y2=y2+(3*q+1)*HUU;
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

int main(){
	xx from, to;
	
	while(scanf("%lu%lu", &from, &to)!=EOF){
		printf("%.3lf\n", triangle_lattice_distance(from, to));
	}
	
	return 0;
}
