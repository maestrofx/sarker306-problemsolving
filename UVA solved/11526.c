#include<stdio.h>
#include<math.h>

long long H(long long n){
    long long res = 0, i, k=sqrt(n), m;
    
    for(i=1;i<k;i++){
		m=n/i;
		res+=m+i*(m-n/(i+1));
    }
    m=n/k;
    res+=m;
    if(m!=k) res+=k;
    
    return res;
} 

int main(){
    long long n;
    int t;
    scanf("%d", &t);
    
    while(t--){
        scanf("%I64d", &n);
        printf("%I64d\n", (n<1)? 0 : H(n));
    }
    
    return 0;
}
