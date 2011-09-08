#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXPOINT 205
#define MAXROAD MAXPOINT*MAXPOINT
#define EPS 1e-6
#define INF 9999999.9

typedef struct{
	double x, y;
}pos;

pos vertices[MAXPOINT];
double matrix[MAXPOINT][MAXPOINT];

double distance(pos u, pos v){
	double delx=u.x-v.x, dely=u.y-v.y;
	return sqrt(delx*delx+dely*dely);
}

double max(double a, double b){
	return (a>b)?a:b;
}

double min(double a, double b){
	return (a<b)?a:b;
}

void init(long N){
	long i, j;
	
	for(i=0;i<=N;i++){
		for(j=0;j<=N;j++){
			matrix[i][j]=INF;
		}
	}
}

void floyd_warshal_minmax(long N){
	long i, j, k;
	
	for(k=0;k<N;k++){
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				if(matrix[i][k]!=INF && matrix[k][j]!=INF){
					matrix[i][j]=min(matrix[i][j], max(matrix[i][k],matrix[k][j]));
				}
			}
		}
	}
}

int main(){
	long test=1, N, i, j;
	pos x;
	
	while(scanf("%ld", &N)!=EOF && N){
		for(i=0;i<N;i++){
			scanf("%lf%lf", &x.x, &x.y);
			vertices[i]=x;
		}   
		init(N);
		for(i=0;i<N;i++){
			for(j=i+1;j<N;j++){
				matrix[i][j]=matrix[j][i]=distance(vertices[i], vertices[j]);
			}
		}
		
		floyd_warshal_minmax(N);
		printf("Scenario #%ld\nFrog Distance = %.3lf\n", test++, matrix[0][1]);
		printf("\n");
	}
	
	return 0;
}
