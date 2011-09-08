#include<stdio.h>
#define MAX 100

typedef long long llong;

typedef struct poly{
	long degree;
	llong coeff[MAX+5];
}poly;

void show_poly(poly a){
	long i=0;
	llong x;
	char sign='+', flag=0;
	
	if(a.degree>1) printf("x^%ld", a.degree), flag=1;
	else if(a.degree)printf("x"), flag=1;
	for(i=1;i<a.degree;i++){
		x=a.coeff[i];
		if(x){
			flag=1;
			sign=(x>=0)? '+' : '-';
			if(sign=='-') x=-x;
			printf(" %c", sign);
			if(x==1){
				printf(" x");
			}
			else if(x) printf(" %lldx", x);
			if(i+1!=a.degree) printf("^%ld", a.degree-i);
		}
	}
	x=a.coeff[i];
	sign=(x>=0)? '+' : '-';
	if(sign=='-') x=-x;
	if(flag) putchar(' ');
	printf("%c", sign);
	printf(" %lld = 0", x);
	printf("\n");
}

void poly_multiply(poly *c, poly *a, poly *b){
	long i, j;
	
	c->degree=a->degree+b->degree;
	for(i=0;i<=c->degree;i++) c->coeff[i]=0;
	for(i=0;i<=a->degree;i++){
		for(j=0;j<=b->degree;j++){
			c->coeff[i+j]+=a->coeff[i]*b->coeff[j];
		}
	}
}

int main(){
	poly a, b, c;
	long i, n;
	llong x;
	
	/* while(scanf("%ld%ld", &a.degree, &b.degree)!=EOF){
		for(i=0;i<=a.degree;i++) scanf("%lld", &a.coeff[i]);
		for(i=0;i<=b.degree;i++) scanf("%lld", &b.coeff[i]);
		poly_multiply(&c, &a, &b);
		show_poly(c);
	} */
	
	while(scanf("%ld", &n)!=EOF){
		a.degree=0, a.coeff[0]=a.coeff[1]=0;
		if(n){
			scanf("%lld", &x);
			a.degree=1, a.coeff[0]=1, a.coeff[1]=-x;
		}
		for(i=1;i<n;i++){
			scanf("%lld", &x);
			b.degree=1, b.coeff[0]=1, b.coeff[1]=-x;
			poly_multiply(&c, &a, &b);
			a=c;
		}
		show_poly(a);
	}
	
	return 0;
}
