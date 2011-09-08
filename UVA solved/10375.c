#include<stdio.h>

double ratio(int p, int q, int r, int s){
	int i;
	double xxx=1;
	
	if(q>s){
		for(i=0;i<s;i++){
			xxx*=(p-i)/(1.0*(r-i));
		}
		for(;i<q;i++){
			xxx*=(p-i)/(1.0*(i+1));
		}
	}
	else{
		for(i=0;i<q;i++){
			xxx*=(p-i)/(1.0*(r-i));
		}
		for(;i<s;i++){
			xxx*=(i+1)/(1.0*(r-i));
		}
	}
	
	return xxx;
}

int main(){
	int p, q, r, s;
	
	while(scanf("%d%d%d%d", &p, &q, &r, &s)!=EOF){
		printf("%.5lf\n", ratio(p, q, r, s));
	}
	
	return 0;
}
