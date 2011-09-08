#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

char num[1005];

int main(){
	int test, n, flag, x, mod, i;
	
	scanf("%d", &test);
	while(test--){
		flag=1;
		scanf("%s", num);
		scanf("%d", &n);
		while(n--){
			scanf("%d", &x);
			if(!flag) continue;
			for(i=0, mod=0;num[i];i++){
				mod=10*mod+(num[i]-'0');
				mod%=x;
			}
			if(mod) flag=0;
		}
		printf("%s - %s.\n", num, (!flag)? "Simple":"Wonderful");
	}
	
    return 0;
}
