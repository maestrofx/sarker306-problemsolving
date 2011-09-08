#include<stdio.h>
#include<string.h>

#define SIZE 350
#define QUEUESIZE 100000

enum color{white='0', gray, black};

char grid[SIZE][SIZE];
char mark[SIZE][SIZE][4];
long distance[SIZE][SIZE][4];
int xdir[]={1,0,0,-1};
int ydir[]={0,1,-1,0};

int rownum, colnum;
int st_x, st_y, en_x, en_y;

typedef struct{
	int i, j;  /*for position on grid*/
	int k;     /*for steps needed to come to that position, 1 2 3.. */
}pos;

pos queue[QUEUESIZE+5];
int head, tail;

void enqueue(pos u){
	queue[tail++]=u;
	if(tail==QUEUESIZE) tail=0;
}

pos dequeue(){
	pos x=queue[head++];
	if(head==QUEUESIZE) head=0;
	return x;
}

void init(){
	int i, j, k;
	
	for(i=0;i<rownum;i++){
		for(j=0;j<colnum;j++){
			for(k=0;k<4;k++){
				mark[i][j][k]=white;
				distance[i][j][k]=99999999;
			}
		}
	}
	
	return;
}

int ingrid(int i, int j){
	if(i<0 || i>rownum) return 0;
	if(j<0 || j>colnum) return 0;
	return 1;
}

int safe(int i, int j, int x, int y){
	int m;
	
	if(ingrid(i, j)==0) return 0;
	if(grid[i][j]=='#') return 0;
	if(i==x){
		if(j>=y){
			for(m=y;m<=j;m++){
				if(grid[i][m]=='#') return 0;
			}
		}
		else{
			for(m=j;m<=y;m++){
				if(grid[i][m]=='#') return 0;
			}
		}
	}
	else if(j==y){
		if(i>=x){
			for(m=x;m<=i;m++){
				if(grid[m][j]=='#') return 0;
			}
		}
		else{
			for(m=i;m<=x;m++){
				if(grid[m][j]=='#') return 0;
			}
		}
	}

	return 1;
}

void bfs(int x, int y){
	int i, j, k, l;
	pos u, v;
	
	init();
	u.i=x, u.j=y, u.k=0;
	distance[x][y][0]=0;
	mark[x][y][0]=gray;
	enqueue(u);
	
	while(head!=tail){
		u=dequeue();
		k=u.k+1;
		if(k>3) k=1;
		for(l=0;l<4;l++){
			i=u.i+k*xdir[l];
			j=u.j+k*ydir[l];
			if(safe(i,j, u.i, u.j)==1 && mark[i][j][k]==white){
				mark[i][j][k]=gray;
				distance[i][j][k]=distance[u.i][u.j][u.k]+1;
				v.i=i, v.j=j, v.k=k;
				enqueue(v);
			}
		}
		
		mark[u.i][u.j][u.k]=black;
	}
}
	
	

int main(){
	int test;
	int i, j;
	char ch;
	
	scanf("%d", &test);
	for(;test; test--){
		scanf("%d%d", &rownum, &colnum);
		
		getchar();
		for(i=0;i<rownum;i++){
			scanf("%s", grid[i]);
			for(j=0;j<colnum;j++){
				ch=grid[i][j];
				switch(ch){
					case 'S' : st_x=i, st_y=j; break;
					case 'E' : en_x=i, en_y=j; break;
				}
			}
		}
		
		/*for(i=0;i<rownum;i++){
			printf("%s\n", grid[i]);
		}
		printf("%d %d %d %d\n", st_x, st_y, en_x, en_y);*/
		
		bfs(st_x, st_y);
		for(i=0, j=99999999;i<4;i++){
			if(j>distance[en_x][en_y][i]){
                j=distance[en_x][en_y][i];
			}
		}
		
		if(j==99999999){
			printf("NO\n");
		}
		else printf("%ld\n", j);
	}
	
	return 0;
}

