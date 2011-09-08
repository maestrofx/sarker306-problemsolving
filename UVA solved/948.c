#include<stdio.h>

long fibonacci[50];
int count;

int main(){
	int i, j, mid, test;
	long n;
	
	for(fibonacci[1]=1, i=2; fibonacci[i-1]<=100000000;i++){
		fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
	}
	count=i;
	//printf("%d\n", count);
	scanf("%ld", &test);
	while(test--){
		scanf("%ld", &n);
		i=count-1, j=0;
		while(j<i){
			mid=(i+j)/2;
			if(fibonacci[mid]>n) i=mid;
			else j=mid;
			if(fibonacci[mid]==n || (fibonacci[mid]<n && fibonacci[mid+1]>n)) break;
		}
		
		//printf("%d %ld ", mid, fibonacci[mid]);
		
		printf("%ld = ", n);
		for(i=mid;i>1;i--){
			if(fibonacci[i]<=n) printf("1"), n-=fibonacci[i];
			else printf("0");
		}
		printf(" (fib)\n");
	}
	
	return 0;
}
