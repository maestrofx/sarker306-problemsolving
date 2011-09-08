#include<stdio.h>

char judge[50], team[50];

int main(){
	int i, j, test, n, flag;
	
	scanf("%d", &test);
	getchar();
	for(n=1;n<=test;n++){
		flag=3;
		gets(team);
		gets(judge);
		for(i=0, j=0;team[i] || judge[j]; i++){
			if(team[i]!=judge[j]){
				if(team[i]==' ' || team[i]=='\t') flag=2;
				else{
					flag=0;
					break;
				}
			}
			else j++;
		}
		
		printf("Case %d: ", n);
		if(flag==3) printf("Yes");
		else if(flag==0) printf("Wrong Answer");
		else printf("Output Format Error");
		printf("\n");
	}
	
	return 0;
}
