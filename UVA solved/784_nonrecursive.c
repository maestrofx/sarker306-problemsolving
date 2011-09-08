#include<stdio.h>
#define STACKSIZE 100000
char maze[40][90];
int row;
int xdir[]={-1, 0, 1, 0};
int ydir[]={0, 1, 0, -1};

typedef struct{
    char r, c;
}pos;
pos stack[STACKSIZE+1];
long top;

void push(pos x){
    stack[top]=x;
    if(STACKSIZE==top) while(1);
    top++;
}

pos pop(){
    pos x;
    
    if(top==0) while(1);
    x=stack[--top];
    return x;
}

void maze_paint(int r, int c){
    int i, x, y;
    pos u, v;
    
    u.r=r, u.c=c;
    push(u);
    
    while(top){
        u=pop();
        r=u.r, c=u.c;
        
        if(maze[r][c]=='*' || maze[r][c]==' '){
            maze[r][c]='#';
            for(i=0;i<4;i++){
                x=r+xdir[i];
                y=c+ydir[i];
                
                if(x<0 || maze[x][y]==0 || y<0) continue;
                
                v.r=x, v.c=y;
                push(v);
            }
        }
    }
}

int main(){
    int i, n, j, startx, starty, endofmaze;
    
    while(scanf("%d", &n)!=EOF){
        getchar();
        while(n--){
            startx=0, starty=0, endofmaze=0;
            for(i=0; ;i++){
                gets(maze[i]);
                for(j=0, endofmaze=1;maze[i][j];j++){
                    if(maze[i][j]!='_') endofmaze=0;
                    if(maze[i][j]=='*') startx=i, starty=j;
                }
                
                if(endofmaze==1){
                    row=i+1;
                    break;
                }
            }
            
            maze_paint(startx, starty);
            for(i=0;i<row;i++) puts(maze[i]);
        }
    }
    
    return 0;
}
