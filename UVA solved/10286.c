#include<stdio.h>
#include<math.h>

int main()
{
    double ratio=1.0673956817111818692592637626719, d;

    while(scanf("%lf", &d)!=EOF) printf("%.10lf\n", ratio*d);

    return 0;
}
