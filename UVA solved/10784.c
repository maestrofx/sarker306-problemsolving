#include<stdio.h>
#define EPS 1e-6

double squareroot(double n){
	double root=0, x, diff;
	long long m=(long long)n, i;
	
	for(i=0;m;i++, m/=10);
	if(i&1){
        for(x=2, i=(i-1)>>1;i;i--, x*=10);
    }
    else{
        for(x=7, i=(i-2)>>1;i;i--, x*=10);
    }
    
	do{
		root=(x+n/x)/2;
		diff=root-x;
		if(diff<0) diff=-diff;
		if(diff<EPS) return root;
		x=root;
	}while(1);
}

int main(){
	long long n;
	int test=0;
	double side;
	
	while(scanf("%lld", &n)!=EOF && n>0){
		side=(squareroot(8*n+9)+3)/2;
		if(side-(long)side>EPS) side+=1;
		printf("Case %d: %ld\n", ++test, (long)side);
	}
	
	return 0;
}
