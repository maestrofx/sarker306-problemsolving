#include<stdio.h>
#include<math.h>

#define PI 3.1415926535897932384626433832795

int main()
{
    long D, V;
    double temp;
    
    while(scanf("%ld%ld", &D, &V)!=EOF && D || V)
    {
        temp=(log(D*D*D-6*V/PI))/3;
        printf("%.3lf\n", exp(temp));
    }
    
    return 0;
}
