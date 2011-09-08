#include<stdio.h>

long long Divide_Conquer_Fib(long long n, long long mod) { 
	long long i, j, h, k, t;
	
	i = h = 1; 
	j = k = 0; 
	while (n > 0) { 
		if (n%2 == 1) {
			t = (j*h)%mod; 
			j = (i*h + j*k + t)%mod; 
			i = (i*k + t)%mod; 
		} 
		t = (h*h)%mod; 
		h = (2*k*h + t)%mod; 
		k = (k*k + t)%mod; 
		n = (long long) n/2; 
	}
	return j%mod;
}

long long power(int base, int pow){
	long long val;
	if(pow==0) return 1;
	if(pow%2) return base*power(base, pow-1);
	else{
		val=power(base, pow>>1);
		return val*val;
	}
}

int main(){
	int pow;
	long long n, x;
	
	while(scanf("%I64d%d", &n, &pow)!=EOF){
		x=power(2,pow);
		printf("%I64d\n", Divide_Conquer_Fib(n, x));
	}
	
	return 0;
}
