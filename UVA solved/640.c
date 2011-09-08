#include<stdio.h>

#define SIZE 1000000

long parent[SIZE+10];

int main(){
	long i;
	long n, x;
	
	for(i=1;i<=SIZE;i++){
		for(n=i, x=i; n; x+=n%10, n/=10);
		if(x<SIZE)parent[x]=i;
	}
	
	for(i=1;i<=SIZE;i++){
		if(parent[i]==0) printf("%ld\n", i);
	}
	
	return 0;
}
