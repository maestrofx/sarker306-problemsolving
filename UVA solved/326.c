#include<stdio.h>
#define SIZE 20
long long comb[101][51];

long long nCr(long n, long r)
{
    long long x;

	if(r==0) x=1;
	else if(n<101 && r<51 && comb[n][r])
		x=comb[n][r];
	else if(2*r>n)
		x=nCr(n, n-r);
	else
		x=nCr(n-1,r) + nCr(n-1,r-1);
	if(n<101 && r<51 && !comb[n][r])
		comb[n][r]=x;

	return x;
}

int main()
{
  	long long Y[SIZE], X[SIZE], sum;
  	long n,i,j, k;
  	double prod;
  	long x;
 	while(scanf("%ld", &n)==1&& n)
 	{
		for(i=0;i<n;i++)
  			scanf("%lld", &Y[i]);
		scanf("%ld", &x);
        x+=n;
        k=0;
        for(i=1;i<n;i++){
            X[k++]=Y[0];
            for(j=0;j+i<n;j++){
                Y[j]=Y[j+1]-Y[j];
               /* printf("%lld ", Y[j]);*/
            }

           /* puts("");*/
            for(j=1;j+i<n;j++) if(Y[j]) break;
            if(i+j==n) break;
        }

        if(Y[0]) X[k++]=Y[0];

		for(sum=0, i=0;i<k;i++) sum+=X[i]*nCr(x-1, i);
		printf("Term %ld of the sequence is %lld\n", x, sum);
  }
  return 0;
}
