#include<stdio.h>
#include<math.h>

#define min(A,B) ((A)>(B)) ? (B):(A)

double x,y,c;

double wide(double m,double h,double d)
{
	double temp,sq,ans;
	
	temp=(x*x-d*d)*(y*y-d*d);
	sq=sqrt(temp);
	sq*=2;

	ans=c*c*((x*x) + (y*y) - 2*d*d + sq) - temp;

	if(h-m<=0.000000001)		return	d;
	else if(ans>0)				return	wide(m,d,(m+d)/2);
	else						return	wide(d,h,(h+d)/2);
}

int main()
{
	double d,ans;

	while(scanf("%lf %lf %lf",&x,&y,&c)!=EOF)
	{
		d=min(x,y);
		ans=wide(0,d,d/2);

		printf("%.3lf\n",ans);
	}

	return 0;
}
