#include<stdio.h>

int main(){
	char ch, flag=0;
	long sum=0, degree, x;
	
	while((ch=getchar())!=EOF){
		if(ch<'0' || ch>'9'){
			if(sum==0) break;
			degree=0;
			while(sum%9==0){
				degree++;
				if(sum==9) break;
				for(x=0; sum; sum/=10){
					x+=sum%10;
				}
				sum=x;
			}
			
			if(degree==0){
				printf(" is not a multiple of 9.\n");
			}
			else{
				printf(" is a multiple of 9 and has 9-degree %ld.\n", degree);
			}
			
			sum=0;
			flag=0;
		}
		
		else{
			sum+=ch-'0';
			if(flag){
				putchar(ch);
			}
			else if(ch!='0'){
				putchar(ch);
				flag=1;
			}
		}
	}
	
	return 0;
}
