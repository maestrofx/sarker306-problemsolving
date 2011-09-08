#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef long long llong;
llong N, xxx, number[20], M;

int cmp(const void *x, const void *y){
    llong *a=(llong*)x, *b=(llong*)y;
    if(*a>*b) return 1;
    else if(*a==*b) return 0;
    else return -1;
}

llong lcm(llong a, llong b){
    llong m=a, n=b, temp;
    
    if(m<n) m^=n^=m^=n;
    while(n) { temp=m; m=n; n=temp%n; }
    m=a*b/m;
    if(m>N) return -1;
    else return m;
}

void inclu_exclu(llong A, long index, int sign){
    llong i, _lcm, j;
    
    for(i=index;i<M;i++){
        _lcm=lcm(A, number[i]);
        if(_lcm==-1) continue;
        /*for(j=0;j<index;j++) printf(" ");
        printf("%lld : %lld\n", _lcm, sign*(N/_lcm));*/
        xxx+=(N/_lcm)*sign;
        inclu_exclu(_lcm, i+1, -sign);
    }
    
    return;
}

int main(){
    llong i;
    
    while(scanf("%lld%lld", &N, &M)!=EOF){
        for(i=0;i<M;i++) scanf("%lld", &number[i]);
        xxx=0;
        for(i=0;i<M;i++){
            /*printf("%lld : %lld\n", number[i], N/number[i]);*/
            xxx+=N/number[i];
            inclu_exclu(number[i], i+1, -1);
        }
        
        printf("%lld\n", N-xxx);
    }
}
