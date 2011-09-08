#include<stdio.h>
#include<math.h>

int main(){
	int n, sum, i, h=0;
	double r;
	
	while(scanf("%d", &n)!=EOF){
		if(h) puts("");
		r=n-0.5;
		
		for(i=1, sum=0;i<n;i++){
			sum+=4*floor(sqrt(r*r-i*i));
		}
		
		printf("In the case n = %d, %d cells contain segments of the circle.\nThere are %d cells completely contained in the circle.\n", n, 8*n-4, sum);
		h=1;
	}
	
	return 0;
}
