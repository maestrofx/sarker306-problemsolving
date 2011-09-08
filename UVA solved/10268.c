#include<stdio.h>
#define MAX 1000000

typedef long long llong;
llong coeff[MAX+5];
long counter;

llong fderive(llong n){
	long i=0;
	llong ans=0;
	for(i=0, counter--;i<=counter;i++) coeff[i]*=counter-i;
	for(i=0, counter--;i<=counter;i++) ans=ans*n+coeff[i];
	return ans;
}

int main(){
	llong n=0, x;
	char ch, sign=1, flag=0, istakingnum=0;
	
	while(scanf("%lld", &x)!=EOF){
		if((ch=getchar())=='\n') while((ch=getchar())!=EOF){
			if(ch=='+' || ch=='-') sign=(ch=='-')? -1:1;
			else if(ch>='0' && ch<='9') n=10*n+ch-'0', istakingnum=1;
			else{
				n*=sign;
				if(istakingnum){
					coeff[counter++]=n;
					/* printf("%lld ", n); */
				}				
				n=0, sign=1, istakingnum=0;
				if(ch=='\n') break;
			}
		}
		
		printf("%lld\n", fderive(x));
		counter=0;
	}
	
	return 0;
}
