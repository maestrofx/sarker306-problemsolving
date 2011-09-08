#include<cstdio>
#include<queue>

using namespace std;

int xdir[]={-1, 0, 1, 0};
int ydir[]={0, 1, 0, -1};

class pos{
public:
    int dir[4];
    int dis;
    int parent;
    
    pos(){
        for(int i=0; i<4; i++) dir[i]=1;
        dis=-1;
        parent=-1;
    }
};

void print_path(pos grid[6][6], int u){
    int x=u/6, y=u%6, v, xx, yy;
    
    if(u==-1) return;
    if(x>=0 && x<6 && y>=0 && y<6)
    if(grid[x][y].parent!=-1){
        v=grid[x][y].parent;
        if(v!=-1)print_path(grid, v);
        xx=v/6, yy=v%6;
        if(xx==x-1) putchar('S');
        else if(xx==x+1) putchar('N');
        else if(yy==y+1) putchar('W');
        else putchar('E');
    }
}

int bfs(pos grid[6][6], int source, int dest){
    int i, u, v, x, y, xx, yy;
    queue<int>Queue;
    
    while(Queue.empty()==false) Queue.pop();
    Queue.push(source);
    grid[source/6][source%6].dis=0;
    
    while(Queue.empty()==false){
        u=Queue.front();
        //printf("%d ", u);
        x=u/6, y=u%6;
        if(u==dest){
            print_path(grid, dest);
            puts("");
            return grid[x][y].dis;
        }
        for(i=0;i<4;i++){
            if(grid[x][y].dir[i]){
                xx=x+xdir[i], yy=y+ydir[i];
                
                if(xx>=0 && xx<6 && yy>=0 && yy<6){
                    if(grid[xx][yy].dis<0){
                        grid[xx][yy].dis=grid[x][y].dis+1;
                        grid[xx][yy].parent=u;
                        Queue.push(xx*6+yy);
                    }
                }
            }
        }
        
        Queue.pop();
    }
    
    return -1;
}

int main(){
    int stx, sty, enx, eny, a, b, c, d;
    
    while(scanf("%d%d", &sty, &stx)!=EOF && (stx || sty)){
        scanf("%d%d", &eny, &enx);
        
        pos grid[6][6];
        for(int i=0;i<3;i++){
            scanf("%d%d%d%d", &a, &b, &c, &d);
            
            if(a==c){
                for(--d; b<=d; b++){
                    if(a>0) grid[b][a-1].dir[1]=0;
                    grid[b][a].dir[3]=0;
                }
            }
            else{
                for(--c;a<=c;a++){
                    if(b>0) grid[b][a].dir[0]=0;
                    grid[b-1][a].dir[2]=0;
                }
            }
        }
        
        /*for(int i=0;i<6;i++){
            for(int j=0;j<6;j++){
                printf("%d%d%d%d ", grid[i][j].dir[0],grid[i][j].dir[1],grid[i][j].dir[2],grid[i][j].dir[3]);
            }
            puts("");
        }*/
        
        stx--, sty--, enx--, eny--;
        bfs(grid, sty+6*stx, eny+6*enx);
    }
    
    return 0;
}
