#include<stdio.h>
#include<math.h>

int main(){
    int n, test;
    double x, y, rat=log(2)/log(10);

    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &n);
            x=-n*rat;
            y=x-(long)x;
            printf("2^-%d = %.3lfE%d\n", n, pow(10, y)*10, (long)x-1);
        }
    }

    return 0;
}
