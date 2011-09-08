#include<stdio.h>
#include<math.h>

typedef long long llong;

int main(){
    llong n;
    llong x, y, z, mix, miy;
    llong i, j, k;
    int flag;
    
    while(scanf("%lld", &n)!=EOF && n>0){
        flag=0;
        miy=mix=99999999;
        k=pow(n, 1.0/3)+0.5;
        /*k=sqrt(n)+0.5;*/
        for(i=1;i<=k;i++){
            if(n%i==0){
                x=i;
                y=n/x-x*x;
                if(y>0 && y%3==0){
                    y/=3;
                    z=sqrt(x*x+4*y)+0.5;
                    if(z*z==x*x+4*y){
                        flag=1;
                        x=(z+x)/2;
                        y=x-i;
                        if(miy>y) miy=y, mix=x;
                    }
                }
                x=n/i;
                y=n/x-x*x;
                if(y>0 && y%3==0){
                    y/=3;
                    z=sqrt(x*x+4*y)+0.5;
                    if(z*z==x*x+4*y){
                        flag=1;
                        x=(z+x)/2;
                        y=x-i;
                        if(miy>y) miy=y, mix=x;
                    }
                }
            }
        }
        
        if(flag==0)printf("No solution\n");
        else printf("%lld %lld\n", mix, miy);
    }
    
    return 0;
}
