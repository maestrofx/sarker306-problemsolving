#include<stdio.h>
#include<math.h>
#define MAX 2000000001

typedef long long llong;
llong array[MAX/1000];

int main()
{
    llong n, r, t, i, c, p, k, counter;
	
    scanf("%lld",&t);
    for (i=1; i<=t; i++)
    {
        scanf("%lld%lld",&n,&r);
        printf("Case #%lld:",i);
        if (n==r) printf(" 0\n");
        else{
            c=n-r;
            for ( p=1,counter=0, k=sqrt(c)+0.5; p<=k ; p++){
                if (!(c%p)){
					if(p>r) printf(" %lld", p);
					if(c>p*r && c!=p*p) array[counter++]=c/p;
				}
            }
			
			for(;counter;) printf(" %lld", array[--counter]);
            printf("\n");
        }
    }
	
    return 0;
}
