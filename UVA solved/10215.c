#include<stdio.h>
#include<math.h>

int main()
{
    double Length,Width;
    double x,x1,x2;
    while(scanf("%lf%lf",&Length,&Width)==2)
    {
        x=((Width+Length) - sqrt( Width*Width -Width*Length + Length*Length )) /6.0 ;
        x1=0.0;
        if(Length>Width)
        Length=Width;
        x2=Length*0.5;
        printf("%.3lf %.3lf %.3lf\n",x+0.0000001,x1,x2+0.0000001);
    }
    return 0;
}
