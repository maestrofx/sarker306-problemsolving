#include<stdio.h>
#include<math.h>

double x, y, c, p, diff;

int main(){
    double m, d, prevd;
    char flag;
    
    while(scanf("%lf%lf%lf", &x, &y, &c)!=EOF){
        if(x>y) { p=x; x=y; y=p;}
        if(fabs(x-y)>1e-5) for(d=0; ;){
            prevd=d;
            p=sqrt(y*y-x*x+d*d);
            d=(p*c)/(p-c);
            /*printf("  p = %lf d = %lf\n", p, d);*/
            if(fabs(d-prevd)<1e-6) break;
        }
        else d=2*c;
        
        d=sqrt(x*x-d*d);
        printf("%.3lf\n", d);
    }
    
    return 0;
}
