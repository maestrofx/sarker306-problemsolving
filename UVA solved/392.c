#include<stdio.h>

#define MAXDEG 8

long coeff[MAXDEG+5];

int main(){
	int i;
	int flag;
	int power;
	
	/* freopen("data.txt", "w", stdout); */
	while(scanf("%ld", &coeff[0])!=EOF){
		for(i=1;i<=MAXDEG;i++) scanf("%ld", &coeff[i]);
		for(i=0, flag=0;i<=MAXDEG;i++){
			if(coeff[i]){
				if(flag) printf(" %c", (coeff[i]>0)? '+' :'-');
				else if(coeff[i]<0) printf("-");
				flag++;
				if(flag){
					printf("%s", (flag==1)? "":" ");
					if(coeff[i]<0) coeff[i]=-coeff[i];
					power=8-i;
					if(coeff[i]!=1 || (coeff[i]==1 &&power==0)) printf("%ld", coeff[i]);
					if(power>1) printf("x^%d", power);
					else if(power==1) printf("x");
				}
			}
		}
		
		if(flag==0) printf("0");
		printf("\n");
	}
	
	return 0;
}
