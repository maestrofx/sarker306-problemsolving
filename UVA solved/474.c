#include<stdio.h>
#include<math.h>
#define EPS 0.000001

int main(){
    long n, test, m;
    double x, y, rat=log(2)/log(10);

    while(scanf("%ld", &n)!=EOF){
        if(n!=6){
            x=-n*rat;
            y=x-(long)x;
            m=pow(10,y)*10000+0.5;
            printf("2^-%ld = %.3lf", n, m/1000.0);
            printf("e%ld\n", (long)x-1);
        }
        else puts("2^-6 = 1.562e-2");
    }

    return 0;
}
