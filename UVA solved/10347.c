#include<stdio.h>
#include<math.h>

int main(){
	double d, e, f, a, b, c, s;
	
	while(scanf("%lf%lf%lf", &d, &e, &f)!=EOF){
		d*=4*d, e*=4*e, f*=4*f;
		a=(2*d+2*e-f)/9, b=(2*e+2*f-d)/9, c=(2*f+2*d-e)/9;
		if(a<0 || b<0 || c<0) printf("-1.000");
		else{
			a=sqrt(a), b=sqrt(b), c=sqrt(c);
			if(a+b>c && b+c>a && c+a>b){
				s=(a+b+c)/2;
				printf("%.3lf", sqrt(s*(s-a)*(s-b)*(s-c)));
			}
			else printf("-1.000");
		}
		
		printf("\n");
	}
	
	return 0;
}
