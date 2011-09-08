#include<stdio.h>
#include"math.h"

#define PI 3.1415926535897932384626433832795

double x,r,n;
int main()
{
    while(scanf("%lf%lf",&r,&n)==2)
    {
        x=n/2;
        x*=r*r*sin(2*PI/n);
        printf("%.3lf",x);
        puts("");
    }
    return 0;
}
