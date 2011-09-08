/*program to determine the factors of a number. For bigger numbers.*/
#include<stdio.h>
#include<stdlib.h>

#define MAXSIEVE 1000000
#define MAXSQRT 1000 /* sqrt(Maxsieve) */

char prm[MAXSIEVE+2];
void sieve(){
    register long i, j;

    for(i=4;i<MAXSIEVE;i+=2) prm[i]=1;
    for(i=3;i<MAXSQRT;i+=2)
        if(prm[i]==0)
            for(j=i*i;j<MAXSIEVE;j+=i*2) prm[j]=1;
}

#define PRIME 2
#define MAYBE_PRIME 1
#define NOTPRIME 0
#define LIMIT 4611686018427387904LL

typedef struct{
    long long num;
    int freq;
}pos;

pos factored[1000];
int c, distinct_factors;
long long mul_mod(long long x, long long y, unsigned long long mod){
    unsigned long long tmp;

    x%=mod, y%=mod;
    if(y==0) return 0;
    tmp=(LIMIT/y);
    if(x>tmp){
        for(tmp=0;y;y>>=1, x=(x<<1)%mod) if(y&1!=0) tmp=(tmp+x)%mod;
        return tmp;
    }
    else return (x*y)%mod;
}

long long modular_exp(long long b, long long p, long long x){
    long long tmp;

    if(p==0) return 1;
    if(p%2==0){
        tmp=modular_exp(b, p/2, x);
        tmp=mul_mod(tmp, tmp, x);
    }
    else tmp=mul_mod(modular_exp(b, p-1, x), b, x);
    return tmp;
}

int witness(long long a, long long n, long long t, long long u){
    register long long i, x, prevx;

    x=modular_exp(a, u, n);
    for(i=1;i<=t;i++){
        prevx=x;
        x=mul_mod(x, x, n);
        if(x==1 && prevx!=1 && prevx!=n-1) return 1;
    }

    if(x!=1) return 1;
    return 0;
}

int isPrime(long long n){
    long long array[]={1,2,7,61,3,11,13,17,23, 31, 97};
    register long long k, a, s, d, i;
    long long m, x, prevx;

    if(n<MAXSIEVE){
        if(prm[n]==0) return PRIME;
        else return NOTPRIME;
    }
    for(m=n-1, s=d=0;m%2==0; m/=2, s++);
    d=m;

    if(s==0) return NOTPRIME;
    for(k=1;k<10;k++){
        a=array[k];
        if(witness(a, n, s, d)) return NOTPRIME;
    }

    return MAYBE_PRIME;
}

long long f(long long x, long long n){
    long long tmp;

	tmp=(mul_mod(x, x, n)+c)%n;
	while(tmp<0) tmp+=n;

	return tmp;
}

long long gcd(long long m, long long n){
	 register long long temp;

	 while(n){
		temp=m;
		m=n;
		n=temp%n;
	 }

	 return m;
}

long long pollard(long long (*f) (long long, long long), long long n){  /* brent cycle */
    register long long x, y, d, abs_val=1;
    register long k=2, i=1;

	x=y=3;
	d=1;

	if((n&1)==0) d=2;
	else while(1){
        i++;
		x=f(x, n);
		abs_val=(x>y)? x-y : y-x;
		d=gcd(abs_val, n);
		if(d!=1) break;
		/*x=f(x, n);
		if(x>y) abs_val=mul_mod(abs_val, x-y, n);
		else abs_val=mul_mod(abs_val, y-x, n);
		if(i%5==0){
		    d=gcd(abs_val, n);
		    if(d!=1) break;
		}*/
		if(i==k) y=x, k<<=1;
	}

	if(d!=n) return d;
	else return 0;
}

void factorize(long long n){
    int array[]={ 3, 5, -1, 1, -3, -5};
    register int i, j;
    long long value;

    if(n==1 || isPrime(n)!=NOTPRIME){
        factored[distinct_factors].num=n;
        factored[distinct_factors++].freq=1;
        return;
    }

    for(i=0;i<6;i++){
        c=array[i];

        value=pollard(f, n);
        if(value){
            if(isPrime(value)==NOTPRIME){
                factorize(value);
                factorize(n/value);
            }
            else{
                for(j=0; n%value==0; n/=value, j++);
                factored[distinct_factors].num=value;
                factored[distinct_factors++].freq=j;
                if(n!=1) factorize(n);
            }

            return;
        }
    }
}

int cmp(const void *a, const void *b){
    pos *x=(pos*)a, *y=(pos*)b;

    if(x->num < y->num) return -1;
    return 1;
}

int main(){
 	long long a, tmp, test, x;
 	register int i, j;
 	char flag;

    sieve();
	while(scanf("%lld", &test)==1){
        while(test--){
            scanf("%lld", &a);
      		distinct_factors=0;
     		printf("%lld = ", a);

      		factorize(a);
      		qsort(factored, distinct_factors, sizeof(pos), cmp);
      		for(j=flag=0;j<distinct_factors; j=i, flag=1){
                if(flag) printf(" * ");
                for(i=j, x=0; i<distinct_factors && factored[i].num==factored[j].num;){
                    x+=factored[i].freq;
                    i++;
                }
                printf("%lld", factored[j].num);
      		    if(x>1) printf("^%lld", x);
            }

      		puts("");
        }
  	}

 	return 0;
}
