#include<stdio.h>
#include<math.h>
#define PI 3.1415926535897932384626433832795

int main(){
    double angle, r, x, A, B, D, tann, sinn, coss, tmp;
    long n, L, W, theta, test;

    scanf("%ld", &test);
    while(test--){
        scanf("%ld%ld%ld", &L, &W, &theta);
        if(theta){
            angle=theta*PI/180;
            tann=tan(angle);
            sinn=tann/sqrt(1+tann*tann);
            coss=sinn/tann;
            r=W/sinn;
            x=W/tann;
            n=(long)(L/x);
            tmp=L-n*x;
            D=tmp*tann;
            if(n%2==1) D=W-D;
            A=n*r+tmp/coss;
            B=sqrt(L*L+D*D);
            printf("%.3lf\n", A/B);
        }
        else printf("1.000\n");
    }

    return 0;
}
