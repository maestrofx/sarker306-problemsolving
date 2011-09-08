#include<stdio.h>
#include<math.h>

typedef long long llong;

int istrue(llong x, llong y, llong z, llong a, llong b, llong c){
    if(x+y+z==a && x*x+y*y+z*z==c && x*y*z==b && x!=y && y!=z && x!=z) return 1;
    return 0;
}

void sort(llong *x, llong *y, llong *z){
    if(*x>*y) *x^=*y^=*x^=*y;
    if(*x>*z) *x^=*z^=*x^=*z;
    if(*y>*z) *y^=*z^=*y^=*z;
}

int main(){
    llong a, b, c;
    llong x, y, z;
    llong yz, y_z, k;
    llong i, j;
    int test;
    char flag;

    scanf("%d", &test);
    while(test--){
        scanf("%lld%lld%lld", &a, &b, &c);
        if(b==0){
            y_z=a;
            yz=(a*a-c)/2;
            k=sqrt(y_z*y_z-4*yz);
            if(k*k+4*yz==y_z*y_z){
                y=(y_z+k)/2, z=(y_z-k)/2, x=0;
                sort(&x, &y, &z);
                if(istrue(x, y, z, a, b, c)) printf("%lld %lld %lld\n", x, y, z);
                else printf("No solution.\n");
            }
            else printf("No solution.\n");
        }
        else{
            for(i=1, flag=0, j=pow(b, 1.0/3)+0.5;i<=j;i++){
                if(b%i==0){
                    x=i;
                   /* printf("#%lld\n", x);*/
                    yz=b/x;
                    y_z=a-x;
                    k=sqrt(y_z*y_z-4*yz);
                    if(k*k+4*yz==y_z*y_z){
                        y=(y_z+k)/2, z=(y_z-k)/2;
                        sort(&x, &y, &z);
                        if(istrue(x, y, z, a, b, c)){
                            printf("%lld %lld %lld\n", x, y, z);
                            flag=1;
                            break;
                        }
                    }

                    x=-i;
                    /*printf("#%lld\n", x);*/
                    yz=b/x;
                    y_z=a-x;
                    k=sqrt(y_z*y_z-4*yz);
                    if(k*k+4*yz==y_z*y_z){
                        y=(y_z+k)/2, z=(y_z-k)/2;
                        sort(&x, &y, &z);
                        if(istrue(x, y, z, a, b, c)){
                            printf("%lld %lld %lld\n", x, y, z);
                            flag=1;
                            break;
                        }
                    }
                }
            }

            if(flag==0) printf("No solution.\n");
        }
    }

    while(1);
    return 0;
}
