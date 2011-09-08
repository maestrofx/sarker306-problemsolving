#include<stdio.h>
#define MAX 100005

typedef long long llong;
llong coeff[MAX+5];
llong quotient[MAX+5];
long counter;

void syntheticdivide(llong degree, llong *coeff, llong n, llong *quo){
	long i=0;
	llong ans=0;
	/* printf("%lld, %lld\n", degree, n); */
	for(i=1, ans=quo[0]=coeff[0];i<=degree; i++) ans=quo[i]=coeff[i]+ans*n;
	printf("q(x):");
	for(i=0;i<degree;i++) printf(" %lld", quo[i]);
	printf("\nr = %lld\n\n", ans);
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
		
		syntheticdivide(counter-1, coeff, x, quotient);
		counter=0;
	}
	
	return 0;
}
