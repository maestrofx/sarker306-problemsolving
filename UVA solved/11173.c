#include<stdio.h>

int main(){
    long test, n, k;

    while(scanf("%ld", &test)!=EOF){
        while(test--){
            scanf("%ld%ld", &n, &k);
            printf("%ld\n", k^(k>>1));
        }
    }

    return 0;
}
