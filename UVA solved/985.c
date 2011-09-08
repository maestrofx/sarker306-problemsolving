#include<stdio.h>
#define SIZE 502
#define QUEUESIZE 10000000
#define INF 1<<29

char grid[4][SIZE][SIZE][5];
long distance[4][SIZE][SIZE];
int row, col;
char xdir[]={-1, 0, 1, 0};
char ydir[]={0, 1, 0, -1};

typedef struct{
    unsigned position;
    char config;
}pos;
pos queue[QUEUESIZE];
long head, tail;

void enqueue(pos u){
	queue[tail++]=u;
	if(tail==QUEUESIZE) tail=0;
}

pos dequeue(){
	pos x=queue[head++];
	if(head==QUEUESIZE) head=0;
	return x;
}

void print_grids(){
    int j, k, r, c;
    
    for(j=0;j<4;j++){
        for(r=0; r<row; r++){
            for(c=0;c<col;c++){
                printf("%-4s ", grid[j][r][c]);
            }
            puts("");
        }
        puts("");
    }
}

void init(){
    int j, k, r, c;
    
    for(r=0;r<row;r++){
        for(c=0;c<col;c++){
            for(j=0;j<4;j++){
                for(k=0, grid[j][r][c][4]=0;k<4;k++) grid[j][r][c][k]='0';
                distance[j][r][c]=INF;
            }
        }
    }
}

void input(){
    int j, k, r, c;
    long i, lim;
    char input[10];
    
    for(i=0, lim=row*col-1;;i++){
        r=i/col, c=i%col;
        
        if(i>=lim) break;
        scanf("%s", input);
        
        for(j=0;j<4;j++)
            for(k=0;input[k];k++){
                switch(input[k]){
                    case 'N': grid[j][r][c][j%4]='1'; break;
                    case 'E': grid[j][r][c][(j+1)%4]='1'; break;
                    case 'S': grid[j][r][c][(j+2)%4]='1'; break;
                    case 'W': grid[j][r][c][(j+3)%4]='1'; break;
                }
            }
    }
}

void bfs(){
    pos u, v;
    int x, y, i, r, c, config;
    long lim=row*col-1, ans=-1;
    
    head=tail=0;
    u.position=0, u.config=0;
    distance[0][0][0]=0;
    enqueue(u);
    
    while(head!=tail){
        u=dequeue();
        
        if(lim==u.position){
            ans=distance[u.config][row-1][col-1];
            break;
        }
        
        for(i=0, config=u.config, r=u.position/col, c=u.position%col;i<4;i++){
            if(grid[config][r][c][i]=='1'){
                x=r+xdir[i];
                y=c+ydir[i];
            
                if(x>=0 && x<row && y>=0 && y<col && distance[(config+1)%4][x][y]==INF){
                    distance[(config+1)%4][x][y]=distance[config][r][c]+1;
                    v.config=(config+1)%4;
                    v.position=x*col+y;
                    enqueue(v);
                }
            }
        }
    }
    
    if(ans==-1) printf("no path to exit\n");
    else printf("%ld\n", ans);
}

int main(){
    while(scanf("%d%d", &row, &col)!=EOF){
        init();
        input();
       /* print_grids(); */
        bfs();
    }
    
    return 0;
}
