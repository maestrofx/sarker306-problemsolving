#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define SIZE 3005

int child[SIZE+5]; /*sum of all factors */
int len[SIZE+5];  /* length of chain */

int initlen(int n){
	int x;
	
	if(len[n]) return len[n];
	x=initlen(child[n])+1;
	len[n]=x;
	return x;
}

void printchild(int n){
	int x=n;
	
	if(x==1 || x==15) return ;
	do{
		x=child[x];
		printf(" %d", x);
	}while(x!=1 && x!=15);
}

int main(){
	int i, j, n, m, k, l, count=1, max;
	
	for(i=1;i<SIZE;i++){
		for(k=0, n=i; n; k+=n%10, n/=10);
		if(k==0) k=9;
		for(j=i;j<SIZE;j+=i){
			child[j]+=k;
		}
	}
	
	len[1]=len[15]=1;
	for(i=2;i<SIZE;i++){
		initlen(i);
	}
	
	while(scanf("%d%d", &m, &n)!=EOF){
		if(m<0 || m>SIZE) break;
		if(n<0 || n>SIZE) break;
		k=m, l=n;
		if(k>l) k^=l^=k^=l;
		
		for(i=k, max=k;i<=l;i++){
			if(len[max]<len[i]) max=i;
			else if(len[max]==len[i] && max>i) max=i;
		}
		
		printf("Input%d: %d %d\nOutput%d: %d", count, m, n, count, max);
		printchild(max);
		printf("\n");
		count++;
	}
	
    return 0;
}
