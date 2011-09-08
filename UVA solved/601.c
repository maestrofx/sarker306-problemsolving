#include<stdio.h>
#include<string.h>

#define SIZE 90
#define QUEUESIZE 10000

enum color{white='0', gray, black};

char grid[SIZE][SIZE];
char mark[SIZE][SIZE];
int xdir[]={1,0,0,-1};
int ydir[]={0,1,-1,0};
int rownum;
int flag;

typedef struct{
	int i, j;  /*for position on grid*/
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
		for(j=0;j<rownum;j++){
			for(k=0;k<4;k++){
				mark[i][j]=white;
			}
		}
	}

	return;
}

int ingrid(int i, int j){
	if(i<0 || i>rownum) return 0;
	if(j<0 || j>rownum) return 0;
	return 1;
}

int safe(int i, int j){
	int m;

	if(ingrid(i, j)==0) return 0;
	/*switch(flag){
		case 1 :
		case 3 : if(grid[i][j]=='W') return 1;
		case 2 :
		case 4 : if(grid[i][j]=='B') return 1;
	}*/
	if(grid[i][j]=='W'){
		if(flag==1 || flag==3) return 1;
		else return 0;
	}
	
	if(grid[i][j]=='B'){
		if(flag==2 || flag==4) return 1;
		else return 0;
	}
	
	return 0;
}

char usafe(int x, int y){
	int m, n;
	int i;
	char f=0;
	
	for(i=0;i<4;i++){
		m=x+xdir[i];
		n=y+ydir[i];
		switch(flag){
			case 3 : if(ingrid(m, n) && grid[m][n]=='W') f=1; break;
			case 4 : if(ingrid(m, n) && grid[m][n]=='B') f=1; break;
		}
	}
	
	return f;
}

int bfs(int x, int y){
	int i, j, k, l;
	pos u, v;

	init();
	u.i=x, u.j=y;
	mark[x][y]=gray;
	head=tail=0;
	enqueue(u);

	while(head!=tail){
		u=dequeue();
		for(l=0;l<4;l++){
			i=u.i+xdir[l];
			j=u.j+ydir[l];
			if(safe(i,j)==1 && mark[i][j]==white){
				mark[i][j]=gray;
				v.i=i, v.j=j;
				enqueue(v);
			}
		}

		mark[u.i][u.j]=black;
		switch(flag){
			case 1 :
			case 3 : if(u.j==rownum-1) return 1; break;
			case 2 :
			case 4 : if(u.i==rownum-1) return 1;
		}
	}
	
	return 0;
}

int main(){
	int i, n, j, k;
	
	while(scanf("%d", &rownum)!=EOF){
		if(rownum==0) break;
		flag=0;
		for(i=0;i<rownum;i++){
			scanf("%s", grid[i]);
		}
		
		flag=1;
		n=0;
		for(i=0; i<rownum;i++){
			if(grid[i][0]=='W'){
				n=bfs(i,0);
				if(n) break;
			}
		}
		
		if(n==0){
			flag=2;
			for(i=0; i<rownum;i++){
				if(grid[0][i]=='B'){
					n=bfs(0,i);
					if(n) break;
				}
			}
		}
		
		if(n==0){
			flag=3;
			for(i=0;i<rownum;i++){
				for(j=0;j<rownum;j++){
					if(grid[i][j]=='U' && usafe(i, j)){
						grid[i][j]='W';
						for(k=0;k<rownum;k++){
							if(grid[k][0]=='W'){
								n=bfs(k, 0);
								if(n) break;
							}
						}
						grid[i][j]='U';
						if(n) break;
					}
				}
				if(n) break;
			}
		}
		
		if(n==0){
			flag=4;
			for(i=0;i<rownum;i++){
				for(j=0;j<rownum;j++){
					if(grid[i][j]=='U' && usafe(i, j)){
						grid[i][j]='B';
						for(k=0;k<rownum;k++){
							if(grid[0][k]=='B'){
								n=bfs(0, k);
								if(n) break;
							}
						}
						grid[i][j]='U';
						if(n) break;
					}
				}
				if(n) break;
			}
		}
		
		if(n==0) flag=5;
		
		switch(flag){
			case 1 : printf("White has a winning path.\n"); break;
			case 2 : printf("Black has a winning path.\n"); break;
			case 3 : printf("White can win in one move.\n"); break;
			case 4 : printf("Black can win in one move.\n"); break;
			case 5 : printf("There is no winning path.\n"); break;
		}
	}
	
	return 0;
}
