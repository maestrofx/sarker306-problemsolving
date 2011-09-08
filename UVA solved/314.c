#include<stdio.h>

#define INF 1<<29
#define QUEUESIZE 1000000
#define MAXROW 51

char grid[MAXROW+1][MAXROW+1];
long visited[MAXROW+2][MAXROW+2][4];
int xdir[]={-1,0,1,0};
int ydir[]={0,1,0,-1};
int row, col;

void init(){
    int i, j, k;
    
    for(i=0;i<=row;i++){
        for(j=0;j<=col;j++){
            for(k=0;k<4;k++){
                visited[i][j][k]=INF;
            }
        }
    }
}

typedef struct{
    int r, c;
    char dir;
}pos;

pos start, end;
pos queue[QUEUESIZE+1];
long head, tail;

void push(pos x){
    queue[tail]=x;
    tail=(tail==QUEUESIZE)?0:tail+1;
}

pos pop(){
    pos x=queue[head];
    head=(head==QUEUESIZE)?0:head+1;
    return x;
}

void print_grid(){
    int i, j;
    
    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            putchar(grid[i][j]);
        }
        puts("");
    }
    
    puts("");
}

int is_safe(pos ppos){
    if(ppos.r>0 && ppos.r<row && ppos.c>0 && ppos.c<col
        && grid[ppos.r][ppos.c]!='1' && grid[ppos.r-1][ppos.c-1]!='1'
        && grid[ppos.r][ppos.c-1]!='1' && grid[ppos.r-1][ppos.c]!='1'){
            if(visited[ppos.r][ppos.c][ppos.dir]==INF) return 1;
            else return -1;
    }
    
    return 0;
}

long bfs(){
    pos u, v;
    int i, flag;
    
    init();
    head=tail=0;
    if(is_safe(start)>0){
        visited[start.r][start.c][start.dir]=0;
        push(start);
    }
    else return -1;
    
    while(head!=tail){
        u=pop();
        if(u.r==end.r && u.c==end.c) return visited[u.r][u.c][u.dir];
        
        v=u;    /* 90 clockwise */
        v.dir=(u.dir+1)%4;
        if(is_safe(v)>0){
            visited[v.r][v.c][v.dir]=visited[u.r][u.c][u.dir]+1;
            push(v);
        }
        
        v=u;    /* 90 anticlockwise */
        v.dir=(u.dir+3)%4;
        if(is_safe(v)>0){
            visited[v.r][v.c][v.dir]=visited[u.r][u.c][u.dir]+1;
            push(v);
        }
        
        for(v=u, i=1; i<=3;i++){   /* move front */
            v.r+=xdir[u.dir];
            v.c+=ydir[u.dir];
            
            flag=is_safe(v);
            if(flag>0){
                visited[v.r][v.c][v.dir]=visited[u.r][u.c][u.dir]+1;
                if(v.r==end.r && v.c==end.c) return visited[v.r][v.c][v.dir];
                push(v);
            }
            else if(flag==0) break;
        }
    }
    
    return -1;
}

int main(){
    int i, j, n;
    char dir[10];
    
    while(scanf("%d%d", &row, &col)!=EOF){
        if(row==col && col==0) break;
        
        for(i=0;i<row;i++){
            for(j=0;j<col;j++){
                scanf("%d", &n);
                grid[i][j]=(char)(n+'0');
            }
        }
        
        scanf("%d%d%d%d%s", &start.r, &start.c, &end.r, &end.c, dir);
        switch(*dir){
            case 'n' : start.dir=0; break;
            case 'e' : start.dir=1; break;
            case 's' : start.dir=2; break;
            case 'w' : start.dir=3; break;
        }
        
        /*print_grid();*/
        printf("%ld\n", bfs());
    }
    
    return 0;
}
