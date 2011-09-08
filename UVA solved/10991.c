#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(){
	int test;
	double r1, r2, r3, a, b, c, del, area, ang1, ang2, ang3;
	
	scanf("%d", &test);
	
	while(test--){
		scanf("%lf%lf%lf", &r1, &r2, &r3);
		a=r1+r2, b=r2+r3, c=r3+r1;
		del=sqrt((r1+r2+r3)*r1*r2*r3);
		ang1=acos((c*c+a*a-b*b)/(2*c*a));
		ang2=acos((a*a+b*b-c*c)/(2*a*b));
		ang3=acos((b*b+c*c-a*a)/(2*b*c));
		area=del-0.5*(ang1*r1*r1+ang2*r2*r2+ang3*r3*r3);
		printf("%lf\n", area);
	}
	
    return 0;
}
