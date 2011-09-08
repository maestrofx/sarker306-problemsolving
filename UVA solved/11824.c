#include<stdio.h>
#include<stdlib.h>

typedef long long llong;
llong array[50];
int cmp(const void *x, const void *y){
    llong diff=*(llong*)x-*(llong*)y;
    if(diff<0) return 1;
    if(diff==0) return 0;
    return -1;
}

llong bigpow(llong base, int exp){
    llong c;

    if(exp==0) return 1;
    if(exp&1) return base*bigpow(base, exp-1);
    else{
        c=bigpow(base, exp>>1);
        return c*c;
    }
}

int main(){
    int test, count=0, i;
    llong n, sum;

    scanf("%d", &test);
    while(test--){
        while(scanf("%lld", &n) && n){
            array[count++]=n;
        }

        qsort(array, count, sizeof(llong), cmp);
        for(i=0, sum=0; i<count;i++){
         /*   printf("%lld  ", array[i]);*/
            sum+=bigpow(array[i], i+1);
        }
        sum*=2;
        if(sum<=5000000) printf("%lld\n", sum);
        else printf("Too expensive\n");
        count=0;
    }

    return 0;
}
