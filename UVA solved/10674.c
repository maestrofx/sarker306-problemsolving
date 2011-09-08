#include<stdio.h>
#include<math.h>

#define EPS 0.00000001

typedef struct{
	double x1, x2, y1, y2, d;
}_tangent;

_tangent tangents[4]; /* storing touching points and lengths */
int count;

double distance(double a, double b, double a1, double b1){
	double delx, dely;
	delx=a-a1, dely=b-b1;
	return sqrt(delx*delx+dely*dely);
}

void printpoint(double h, double k, double a, double b, double m, double *x, double *y){
	double p=m*m;
	double q=1+p;
	*x=(p*a+(k-b)*m+h)/q;
	*y=(p*k+(h-a)*m+b)/q;
}

void printpoint2(double h, double k, double a, double b, double *x, double *y){ /* when m=inf*/
	*x=a, *y=k;
}

void findpoints(double h, double k, double a, double b, double r, double *x, double *y, double *x1, double *y1){
	double m, m1, mm, s, rat, n;
	
	m=a-h, n=k-b;
	s=sqrt(m*m+n*n);
	rat=r/sqrt(s*s-r*r);
	
	if(h==a || (m<EPS && m>-EPS)){
		m=1/rat, mm=-m;
		printpoint(h, k, a, b, m, x, y);
		printpoint(h, k, a, b, mm, x1, y1);
	}
	else{
		m1=(k-b)/(h-a);
		s=m1*rat+1;
		if(s==0 || (s<EPS && s>-EPS)){
			printpoint2(h, k, a, b, x, y);
		}
		else{
			m=(m1-rat)/s;
			printpoint(h, k, a, b, m, x, y);
		}
		
		s=1-m1*rat;
		if(s==0 || (s<EPS && s>-EPS)){
			printpoint2(h, k, a, b, x1, y1);
		}
		else{
			mm=(m1+rat)/s;
			printpoint(h, k, a, b, mm, x1, y1);
		}
	}
}

void findshoroltangent(double h1, double k1, double r1, double h2, double k2, double r2){
	double A, B, C, C1, K, boo, huu;
	double i, j, m, n, i1, j1, m1, n1;
	double r;
	
	if(r1==r2 || (r1-r2<EPS && r1-r2>-EPS)){
		A=k1-k2, B=h2-h1, C1=h1*k2-h2*k1;
		huu=A*A+B*B;
		boo=r1*sqrt(huu);
		K=A*k1-B*h1;
		C=C1+boo;
		i=-(B*K+A*C)/huu, j=-(B*C-A*K)/huu;
		tangents[count].x1=i, tangents[count].y1=j, tangents[count].x2=i+h2-h1, tangents[count].y2=j+k2-k1;
		tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
		count++;
		C=C1-boo;
		i1=-(B*K+A*C)/huu, j1=-(B*C-A*K)/huu;
		tangents[count].x1=i1, tangents[count].y1=j1, tangents[count].x2=i1+h2-h1, tangents[count].y2=j1+k2-k1;
		tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
		count++;
		return;
	}
	else if(r1>r2){
		A=h1, h1=h2, h2=A;
		A=k1, k1=k2, k2=A;
		A=r1, r1=r2, r2=A;
	}
	findpoints(h2,k2, h1, k1, r2-r1, &i, &j, &i1, &j1);
	m=(r2*i-r1*h2)/(r2-r1), n=(r2*j-r1*k2)/(r2-r1);
	m1=(r2*i1-r1*h2)/(r2-r1), n1=(r2*j1-r1*k2)/(r2-r1);
	tangents[count].x1=m, tangents[count].y1=n, tangents[count].x2=m+h1-i, tangents[count].y2=n+k1-j;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
	tangents[count].x1=m1, tangents[count].y1=n1, tangents[count].x2=m1+h1-i1, tangents[count].y2=n1+k1-j1;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
}

void findtirjoktangent(double h1, double k1, double r1, double h2, double k2, double r2){
	double i, j, m, n, i1, j1, m1, n1;
	
	findpoints(h1, k1, h2, k2, r2+r1, &i, &j, &i1, &j1);
	m=(r1*i+r2*h1)/(r1+r2), n=(r1*j+r2*k1)/(r2+r1);
	m1=(r1*i1+r2*h1)/(r2+r1), n1=(r1*j1+r2*k1)/(r2+r1);
	tangents[count].x1=m, tangents[count].y1=n, tangents[count].x2=m+h2-i, tangents[count].y2=n+k2-j;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
	tangents[count].x1=m1, tangents[count].y1=n1, tangents[count].x2=m1+h2-i1, tangents[count].y2=n1+k2-j1;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
}

void findspcltangent1(double h1, double k1, double r1, double h2, double k2, double r2){
	tangents[count].x1=(r2*h1-r1*h2)/(r2-r1);
	tangents[count].y1=(r2*k1-r1*k2)/(r2-r1);
	tangents[count].x2=tangents[count].x1;
	tangents[count].y2=tangents[count].y1;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
}

void findspcltangent2(double h1, double k1, double r1, double h2, double k2, double r2){
	tangents[count].x1=(r2*h1+r1*h2)/(r2+r1);
	tangents[count].y1=(r2*k1+r1*k2)/(r2+r1);
	tangents[count].x2=tangents[count].x1;
	tangents[count].y2=tangents[count].y1;
	tangents[count].d=distance(tangents[count].x1, tangents[count].y1, tangents[count].x2, tangents[count].y2);
	count++;
}

int compare(_tangent a, _tangent b){
	if(a.x1-b.x1<0 || a.x1-b.x1< -EPS) return -1;
	else if(a.x1-b.x1>0 || a.x1-b.x1>EPS) return 1;
	if(a.y1-b.y1<0 || a.y1-b.y1<-EPS) return -1;
	return 1;
}

int check(int n, double h1, double k1, double r1){
	double xxx=tangents[n].x1-h1, yyy=tangents[n].y1-k1;
	double abb=xxx*xxx+yyy*yyy-r1*r1;
	if(abb<-EPS || abb>EPS) return 1;
	return 0;
}

void change(int n){
	double temp;
	temp=tangents[n].x1;
	tangents[n].x1=tangents[n].x2;
	tangents[n].x2=temp;
	temp=tangents[n].y1;
	tangents[n].y1=tangents[n].y2;
	tangents[n].y2=temp;
}

void print(double h1, double k1, double r1){
	_tangent temp;
	int i, j;
	
	for(i=0;i<count;i++){
		if(check(i, h1, k1, r1)) change(i);
	}
	
	for(i=0;i<count-1;i++){
		for(j=i+1;j<count;j++){
			if(compare(tangents[i], tangents[j])==1){
				temp=tangents[i];
				tangents[i]=tangents[j];
				tangents[j]=temp;
			}
		}
	}
	
	for(i=0;i<count;i++){
		printf("%.5lf %.5lf %.5lf %.5lf %.5lf\n", tangents[i].x1, tangents[i].y1, tangents[i].x2, tangents[i].y2, tangents[i].d);
	}
}

int main(){
	double h1, k1, r1, h2, k2, r2, c1c2;
	double tem, met;
	
	/*freopen("10674.in.txt", "r", stdin);
	freopen("data.txt", "w", stdout);*/
	
	while(scanf("%lf%lf%lf%lf%lf%lf", &h1, &k1, &r1, &h2, &k2, &r2)!=EOF){
		if(h1==0 && k1==0 && r1==0 && h2==0 && k2==0 && r2==0) break;
		count=0;
		c1c2=distance(h1, k1, h2, k2);
		tem=r1-r2; if(tem<0) tem*=-1;
		met=r1+r2;
		if(c1c2==tem || (c1c2-tem<EPS && c1c2-tem>-EPS)){
			if(r1!=r2){
				printf("1\n");
				findspcltangent1(h1, k1, r1, h2, k2, r2);
				print(h1, k1, r1);
			}
			else printf("-1\n"); /* infinite tangents*/
		}
		else if(c1c2<tem){
			printf("0\n"); /* the number of tangents that can be drawn */
		}
		else if(c1c2==met || (c1c2-met<EPS && c1c2-met>EPS)){
			printf("3\n");
			findshoroltangent(h1, k1, r1, h2, k2, r2);
			findspcltangent2(h1, k1, r1, h2, k2, r2);
			print(h1, k1, r1);
		}
		else if(c1c2<met){
			printf("2\n");
			findshoroltangent(h1, k1, r1, h2, k2, r2);
			print(h1, k1, r1);
		}
		else{
			printf("4\n"); /* maximum legitimate tangents */
			findshoroltangent(h1, k1, r1, h2, k2, r2);
			findtirjoktangent(h1, k1, r1, h2, k2, r2);
			print(h1, k1, r1);
		}
	}
	
	return 0;
}
