#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

int main(){
	int a, b, c, d;
	
	while(scanf("%d%d%d%d", &a, &b, &c, &d)!=EOF){
		if(!a && !b && !c && !d) break;
		if(a==c && b==d) printf("0");
		else if(a==c || b==d || a-c==b-d || a-c==d-b) printf("1");
		else printf("2");
		printf("\n");
	}
		
    return 0;
}
