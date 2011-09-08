#include<stdio.h>

typedef unsigned long long ull;
ull comb[201][73];

ull nCr(long n, long r){
    ull x;
    
	if(r==0) x=1;
	else if(n<201 && r<73 && comb[n][r]) x=comb[n][r];
	else if(2*r>n) x=nCr(n, n-r);
	else x=nCr(n-1,r) + nCr(n-1,r-1); 
	if(n<201 && r<73 && !comb[n][r]) comb[n][r]=x;
    
	return x;
}

int main(){
    long n, t, p, test;
    
    while( scanf("%ld", &test) == 1){
        while( test-- ){
            scanf("%ld%ld%ld", &n, &t, &p);
            printf("%llu\n", nCr( t - n*p + n - 1 , n - 1) );
        }
    }
    
    return 0;
}
