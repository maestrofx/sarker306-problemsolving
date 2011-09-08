#include<stdio.h>

#define SIZE 401

long arr[SIZE+5][SIZE+5];

void init(){
	int i, j;

	for(i=0;i<SIZE;i++) arr[i][0]=1;
	for(i=1;i<SIZE;i++){
		for(j=1;j<SIZE;j++){
			arr[i][j]=(arr[i-1][j]+arr[i-1][j-1])%1000007;
		}
	}
}

int main(){
	int m, n, k, huu;
	long sum;
	int test, i;

	init();
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		sum=0;
		scanf("%d%d%d", &m, &n, &k);
		huu=m*n;
		if(k<=huu){
			sum=arr[huu][k]-2*arr[huu-n][k]-2*arr[huu-m][k]+4*arr[huu+1-m-n][k]+arr[huu-2*n][k]+arr[huu-2*m][k]-2*arr[huu+2-2*m-n][k]-2*arr[huu+2-2*n-m][k]+arr[huu+4-2*(m+n)][k];
			sum%=1000007;
			if(sum<0) sum=1000007+sum;
		}
		else sum=0;
		printf("Case %d: %ld\n", i, sum);
	}

	return 0;
}
