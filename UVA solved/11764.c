#include<stdio.h>

int main(){
	int test, n, i;
	int high, low, prev, x;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		high=low=0;
		scanf("%d", &n);
		scanf("%d", &prev);
		while(--n){
			scanf("%d", &x);
			if(x>prev) high++;
			else if(x<prev) low++;
			prev=x;
		}
		
		printf("Case %d: %d %d\n", i, high, low);
	}
	
	return 0;
}
