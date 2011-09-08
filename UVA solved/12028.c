#include <stdio.h>
#include <stdlib.h>

int cmp(const void *x, const void *y){
    return (*(long*)x > *(long*)y) ? -1 : 1;
}

long a[100005], ca[100005];
int main(){
    long k, c, n, i;
    int test, kase;
    unsigned long long ans;
    
    while(scanf("%d", &test)!=EOF){
        for( kase = 1 ; kase <= test ; kase++ ){
            scanf("%ld%ld%ld%ld", &k, &c, &n, a);
            for( i = 1 ; i < n ; i++ ) a[i] = (k * a[i-1] + c)%1000007;
            qsort(a, n, sizeof(long), cmp);
            for( ca[n] = a[n] = 0, i = n - 1 ; i >= 0 ; i-- ){
                ca[i] = ca[i+1] + a[i];
            }
            for( ans = i = 0 ; i < n ; i++ ) ans += -ca[i] + a[i] * (n-i);
            printf("Case %d: %llu\n", kase, ans);
        }
    }
    
    return 0;       
}
