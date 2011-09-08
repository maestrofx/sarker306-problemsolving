#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 10005

double side[MAX];

int cmp(const void *x, const void *y){
	double *a=(double*)x, *b=(double*)y;
	return *a-*b;
}

int main(){
	long test, N, i;
	double a, b, c, s, area,max;
	
	while(scanf("%ld", &test)!=EOF){
		while(test--){
			scanf("%ld", &N);
			for(i=0;i<N;i++) scanf("%lf", side+i);
			qsort(side, N, sizeof(double), cmp);
			max=0.0;
			for(i=0;i+2<N;i++){
				if(side[i]+side[i+1]>side[i+2]){
                    a=side[i], b=side[i+1], c=side[i+2], s=(a+b+c)/2.00;
                    area=(s*(s-a)*(s-b)*(s-c));
    				if(area<0)
    				area*=-1;
    				area=sqrt(area);
    				if(area>max)
    				max=area;
                }
			}
			/*area=((long long)(area*100+0.5))/100.0;*/
			printf("%.2lf\n", max);
		}
	}
	
	return 0;
}
