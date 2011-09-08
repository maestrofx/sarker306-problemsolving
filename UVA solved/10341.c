#include<stdio.h>
#include<math.h>

#define LIM 0.000001

/* p*e-x + q*sin(x) + r*cos(x) + s*tan(x) + t*x2 + u = 0 */

int p, q, r, s, t, u;
	
double f(double x){
	return p*exp(-x) + q*sin(x) + r*cos(x) + s*tan(x) + t*x*x + u;
}

double f1(double x){
	double d=cos(x);
	return -p*exp(-x) + q*d - r*sin(x) + s/(d*d) + 2*t*x;
}

double ternarySearch(double left, double right){
	double leftThird, rightThird;
	printf("%lf %lf er jonno %lf %lf\n", left, right, f(left), f(right));
	
	if ( abs(f(right) - f(left)) < LIM)
        return (left + right)/2;

    leftThird = (2*left + right)/3;
    rightThird = (left + 2*right)/3;

    if (f(leftThird) / f(rightThird) < 0)
        return ternarySearch(leftThird, right);

    return ternarySearch(left, rightThird);
}

int main(){
	int count, flag=0;
	double value, diff, val0, val1, x, x1;
	
	while(scanf("%d%d%d%d%d%d", &p, &q, &r, &s, &t, &u)!=EOF){
		flag=0;
		if(f(0)==0){
			flag=1;
			printf("0.0000\n");
		}
		
		for(x=0;flag==0 && x<=1;x+=0.01){
			if(f(x)/f(x+.01)<0){
				do{
					x1=x-f(x)/f1(x);
					if(x-x1<LIM && x-x1>-LIM) break;
					x=x1;
				}while(1);
				printf("%.4lf\n", x);
				flag=1;
				break;
			}
		}
		
		if(flag==0 && ( x<0 || x>1)) printf("No solution\n");
	}
	
	return 0;
}
