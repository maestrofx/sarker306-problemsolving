#include<stdio.h>
#include<math.h>
#define EPS 1e-6

int main(){
    int test, i;
    double d, u, v;
    
    scanf("%d", &test);
    for(i=1;i<=test;i++){
        scanf("%lf%lf%lf", &d, &v, &u);
        printf("Case %d: ", i);
        if(u>v && ( v!=0 || fabs(v)>EPS) ) printf("%.3lf\n", d/sqrt(u*u-v*v)-d/u);
        else printf("can't determine\n");
    }
    
    return 0;
}
