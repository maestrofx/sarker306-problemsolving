#include<stdio.h>

char maze[40][90];
int row;
int xdir[]={-1, 0, 1, 0};
int ydir[]={0, 1, 0, -1};

void maze_paint(int r, int c){
    int i, x, y;
    
    if(maze[r][c]=='*' || maze[r][c]==' '){
        maze[r][c]='#';
        for(i=0;i<4;i++){
            x=r+xdir[i];
            y=c+ydir[i];
            
            if(x<0 || maze[x][y]==0 || y<0) continue;
            maze_paint(x, y);
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
