#include<stdio.h>
#include<math.h>

long long sum(long long start,long long n){
	long long sum=0, temp=2*start+n-1;
	if(n&1) temp>>=1;
	else n>>=1;
	sum+=n*temp;
	return sum;
}

long long csod(long long n){
    long long res = 0, i, k=sqrt(n), m, x, a;
    
    for(i=2;i<k;i++){
		m=n/i;
		a=n/(i+1);
		x=m-a;
		res+=i*(m-1)+(i-1)*sum(a+1, x);
    }
    
    m=n/k;
    a=n/(k+1);
    res+=k*(m-1);
    if(m!=k) res+=sum(a+1, m-a)*(k-1);
    
    return res;
} 

int main(){
    long long n;
    int t=1;
    
    while(scanf("%I64d", &n)!=EOF){
        if(n==0) break;
        printf("Case %d: %I64d\n", t++, (n<4)? 0 : csod(n));
    }
    
    return 0;
}
