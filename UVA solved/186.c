#include<stdio.h>
#include<string.h>

#define MAXCITIES 102
#define MAXWORDLEN 35
#define INF 99999999

typedef struct{
	long distance;
	char route[30];
}road;
char cities[MAXCITIES+3][MAXWORDLEN+5];
road mat[MAXCITIES+5][MAXCITIES+5];
int path[MAXCITIES+5][MAXCITIES+5];
int count;

void init(void){
	int i, j;
	
	for(i=0;i<=MAXCITIES;i++){
		for(j=0;j<MAXCITIES; j++){
			mat[i][j].distance=INF;
			mat[i][j].route[0]=0;
		}
		cities[i][0]=0;
	}
	count=0;
}

void initpath(void){
	int i, j;
	
	for(i=0;i<=count;i++){
		for(j=0;j<=count;j++){
			path[i][j]=(mat[i][j].distance==INF)? 0 : j;
		}
	}
}

void floyd_warshall(void){
	int i, j, k;
	
	for(k=0;k<count;k++){
		for(i=0;i<count;i++){
			for(j=0;j<count;j++){
				if(mat[i][k].distance!=INF && mat[k][j].distance!=INF){
					if(mat[i][k].distance+mat[k][j].distance<mat[i][j].distance){
						mat[i][j].distance=mat[i][k].distance+mat[k][j].distance;
						path[i][j]=path[i][k];
					}
				}
			}
		}
	}
}

void printcities(void){
	int i=0;
	
	for(i=0;i<count;i++) printf("%s - %d\n", cities[i], i+1);
}

void printmatrix(){
	int i, j;
	
	for(i=0;i<count;i++){
		for(j=0;j<count;j++){
			printf("%6d", (mat[i][j].distance==INF)? 0 : mat[i][j].distance);
		}
		printf("\n");
	}
}

void printpath(int i, int j){
	if(i==j){
		return;
	}
	
	printf("%-20s %-20s %-10s %5d\n", cities[i], cities[path[i][j]], mat[i][path[i][j]].route, mat[i][path[i][j]].distance);
	printpath(path[i][j], j);
}

void printing(int u, int v){
	printf("From                 To                   Route      Miles\n-------------------- -------------------- ---------- -----\n");
	printpath(u, v);
	printf("%58s\n", "-----");
	printf("                                          ");
	printf("%s      %5ld\n", "Total", mat[u][v].distance);				
}

int main(){
	char a[500], b[50], c[50], d[50];
	char ch, *p, *q;
	long x;
	int u, v;
	
	init();
	while(gets(a)){
		if(a[0]==0){
			/*printcities();*/
			initpath();
			floyd_warshall();
			/*printmatrix();*/
			while(gets(a)){
				if(a[0]==0) break;
				for(p=a, q=b; *p!=',';p++, q++) *q=*p;
				*q=0;
				for(++p, q=c;*p!=',';p++, q++) *q=*p;
				*q=0;
				for(u=0;cities[u][0] && u<MAXCITIES;u++){
					if(strcmp(cities[u], b)==0) break;
				}
				for(v=0;cities[v][0] && v<MAXCITIES;v++){
					if(strcmp(cities[v], c)==0) break;
				}
				
				printf("\n\n");
				/*printf("%s %d %s %d\n", b, u, c, v);*/
				if(u!=-1 && v!=-1){
					if(path[u][v] ) printing(u, v);
					else printf("no path");
				}
			}
			
			init();
		}
		else{
			for(p=a, q=b; *p!=',';p++, q++) *q=*p;
			*q=0;
			for(++p, q=c;*p!=',';p++, q++) *q=*p;
			*q=0;
			for(++p, q=d;*p!=',';p++, q++) *q=*p;
			*q=0;
			sscanf(++p, "%ld", &x);
			for(u=0;cities[u][0] && u<MAXCITIES;u++){
				if(strcmp(cities[u], b)==0) break;
			}
			if(cities[u][0]==0) strcpy(cities[u], b), count++;
			for(v=0;cities[v][0] && v<MAXCITIES;v++){
				if(strcmp(cities[v], c)==0) break;
			}
			if(cities[v][0]==0) strcpy(cities[v], c), count++;
			if(mat[u][v].distance==INF){
				mat[v][u].distance=mat[u][v].distance=x;
				strcpy(mat[u][v].route, d);
				strcpy(mat[v][u].route, d);
			}
			/*printf("%s %s %s %ld\n", b, c, d, mat[u][v].distance);*/
		}
	}
	
	return 0;
}
