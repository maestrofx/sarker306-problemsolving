#include<stdio.h>

#define SIZE 1005

int cost[SIZE][SIZE];
char thing[SIZE][SIZE];
char word[SIZE];
int len;

int min_op(int left, int right){
	int value, a, b;
	
	if(cost[left][right]) return cost[left][right];
	if(left>right){
		thing[left][right]=9;
		return 0;
	}
	if(left==right) {
		thing[left][right]=8;
		return 0;
	}
	if(word[left]==word[right]){
		value=min_op(left+1, right-1);
		thing[left][right]=1;       /* diagonally downward*/
	}
	else{
		a=1+min_op(left, right-1);
		b=1+min_op(left+1, right);
		value=(a<b)?a:b;
		if(value==a){
			thing[left][right]=2;    /* horizontally right */
		}
		else{
			thing[left][right]=3;    /* vertically downward*/
		}
	}
	
	cost[left][right]=value;
	
	return value;
}

void print_pal(int i, int j){
	if(thing[i][j]==9) return;
	if(thing[i][j]==8){
		putchar(word[i]);
		return;
	}
	
	if(thing[i][j]==1){
		putchar(word[i]);
		print_pal(i+1, j-1);
		putchar(word[i]);
	}
	else if(thing[i][j]==2){
		putchar(word[j]);
		print_pal(i, j-1);
		putchar(word[j]);
	}
	else if(thing[i][j]==3){
		putchar(word[i]);
		print_pal(i+1, j);
		putchar(word[i]);
	}
}

int main(){
	int i, j, k;
	
	while(scanf("%s", word)!=EOF){
		len=strlen(word);
		for(i=0;i<len;i++){
			for(j=0;j<len;j++){
				thing[i][j]=0;
				cost[i][j]=0;
			}
		}
		
		printf("%d ", min_op(0, len-1));
		
		/*for(i=0;i<len;i++){
			for(j=0;j<len;j++){
				printf("%d ", thing[i][j]);
			}
			printf("\n");
		}*/
		print_pal(0, len-1);
		printf("\n");
	}
	
	return 0;
}

