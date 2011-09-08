#include<stdio.h>
#include<math.h>

int main(){
    int t;
    double r,m1,m2,m3,n1,n2,n3,area,x,y,u,v,a,b,c,s;
    
    scanf("%d",&t);
    while(t--){
        scanf("%lf%lf%lf%lf%lf%lf%lf",&r,&m1,&n1,&m2,&n2,&m3,&n3);
        m1/=(m1+n1);
        n1=1-m1;
        m2/=(m2+n2);
        n2=1-m2;
        m3/=(m3+n3);
        n3=1-m3;
        x=n2/m3;
        y=m2/n1;
        u=x+y;
        v=x-y;
        a=((4*r*r)*(1+u))/((u-1)*(v+1)*(1-v));
        a=sqrt(a);
        /*a=((2*r)*(sqrt(1+u)))/sqrt((u-1)*(v+1)*(1-v));*/
        b=x*a;
        c=y*a;
        s=(a+b+c)/2;
        area=sqrt(s*(s-a)*(s-b)*(s-c));
        printf("%.4lf\n",area);
    }
    
    return 0;
}
