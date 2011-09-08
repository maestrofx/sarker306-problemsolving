#include<stdio.h>
#define MAX 1000

typedef long long llong;
llong coeff[MAX+5];
int counter;

llong f(llong n){
	int i=0;
	llong ans=0;
	for(;i<counter;i++) ans=ans*n+coeff[i];
	return ans;
}

int main(){
	llong n=0;
	char ch, sign=1, flag=0, istakingnum=0;
	
	while((ch=getchar())!=EOF){
		if(ch=='+' || ch=='-') sign=(ch=='-')? -1:1;
		else if(ch>='0' && ch<='9') n=10*n+ch-'0', istakingnum=1;
		else{
			n*=sign;
			if(istakingnum){
				coeff[counter++]=n;
				/* printf("%lld ", n); */
			}				
			n=0, sign=1, istakingnum=0;
			if(ch=='\n'){
				/* printf("\n"); */
				while((ch=getchar())!=EOF){
					if(ch=='+' || ch=='-') sign=(ch=='-')? -1:1;
					else if(ch>='0' && ch<='9') n=10*n+ch-'0', istakingnum=1;
					else{
						n*=sign;
						if(istakingnum){
							if(flag) printf(" ");
							flag=1;
							printf("%lld", f(n));
						}
						n=0, sign=1, istakingnum=0;
						if(ch=='\n'){
							printf("\n");
							counter=flag=0;
							break;
						}
					}
				}
			}
		}
	}
	
	return 0;
}
