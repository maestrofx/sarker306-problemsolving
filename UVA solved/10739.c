#include<stdio.h>
#include<string.h>

#define SIZE 1005

char word[SIZE];
int cost[SIZE][SIZE];
int len;

void init(){
	int i, j;
	
	for(i=0;i<=len;i++){
		for(j=0;j<=len;j++){
			cost[i][j]=0;
		}
	}
}

int cost_pal(int i, int j){
	int x;
	int a, b, c;
	
	if(i>=j) return 0;
	if(cost[i][j]) return cost[i][j];
	
	if(word[i]==word[j]){
		x=cost_pal(i+1, j-1);
	}
	else{
		a=1+cost_pal(i+1, j-1);
		b=1+cost_pal(i+1, j);
		c=1+cost_pal(i, j-1);
		x=(a<b)? a:b;
		x=(x<c)? x:c;
	}
	
	cost[i][j]=x;
	return x;
}

int main(){
	int test, i;
	
	scanf("%d", &test);
	for(i=1;i<=test;i++){
		scanf("%s", word);
		len=strlen(word);
		init();
		printf("Case %d: %d\n", i, cost_pal(0, len-1));
	}
	
	return 0;
}

		
