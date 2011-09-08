#include<stdio.h>

#define SIZE 10000000
#define GRAY 1
#define BLACK 2
#define WHITE 0

int globe;
long happy[SIZE];
char visited[SIZE];

long ishappy(long n){
	long flag=0;
	long i, x, p;
	char str[15];
	
	if(globe==2)printf("%ld entered\n", n);
	if(n<SIZE && visited[n]==BLACK) return happy[n];
	if(n<SIZE && visited[n]==GRAY) return 0;
	
	if(n<SIZE) visited[n]=GRAY;
	sprintf(str, "%d", n);
	for(i=0, x=0;str[i];i++){
		p=str[i]-'0';
		x+=p*p;
	}
	
	flag=ishappy(x);
	if(flag!=0) flag++;

	if(n<SIZE){
		happy[n]=flag;
		visited[n]=BLACK;
	}
	
	return flag;
}

int main(){
	long int i, j, a, b;
	
	happy[1]=1;
	visited[1]=BLACK;
	
	for(i=2;i<100000;i++){
		j=ishappy(i);
		if(!happy[i]) happy[i]=j;
		/*if(j) printf("%4d - %d\n", i, j);*/
	}
	
	while(scanf("%ld%ld", &a, &b)!=EOF){
		if(globe==1) printf("\n");
		for(i=a;i<=b;i++){
			j=ishappy(i);
			if(j) printf("%ld %ld\n", i, j);
		}
		globe=1;
	}
	
	globe=2;
	/*while(scanf("%ld", &i)!=EOF){
		printf("%ld\n", ishappy(i));
	}*/
	
	return 0;
}
