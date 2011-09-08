#include<cstdio>
#include<queue>

#define SIZE 1001
char grid[SIZE+1][SIZE+1];
long times[SIZE+1][SIZE+1];
int row, col, joex, joey;

void init(int r, int c){
    int i, j;
    
    for(i=0;i<=r;i++){
        for(j=0;j<=c;j++){
            times[i][j]=grid[i][j]=0;
        }
    }
}

typedef struct{
    int x, y;
}pos;

int xdir[]={-1,0,1,0};
int ydir[]={0,1,0,-1};

long bfs(){
    std::queue<pos>joe, fire, temp;
    pos u, v;
    int i, x, y, stillPossible;
    long time=0;
    
    u.x=joex, u.y=joey;
    joe.push(u);
    for(x=0;x<row;x++){
        for(y=0;y<col;y++){
            if(grid[x][y]!='F') continue;
            u.x=x, u.y=y;
            fire.push(u);
        }
    }
    
    while(joe.empty()==false){
        while(joe.empty()==false){
            temp.push(joe.front());
            joe.pop();
        }
        
        ++time;
        while(temp.empty()==false){
            u=temp.front();
            
            if(grid[u.x][u.y]=='J'){
                //std::printf("joe at %d %d\n", u.x, u.y);
                for(i=0;i<4;i++){
                    v.x=u.x+xdir[i];
                    v.y=u.y+ydir[i];
                    if(v.x<0 || v.x>=row || v.y<0 || v.y>=col) return time;
                    if(grid[v.x][v.y]=='.'){
                        grid[v.x][v.y]='J';
                        joe.push(v);
                    }
                }
            }
            
            temp.pop();
        }
        
        if(joe.empty()==true) break;
        
        while(fire.empty()==false){
            temp.push(fire.front());
            fire.pop();
        }
        
        while(temp.empty()==false){
            u=temp.front();
            //std::printf("fire at %d %d\n", u.x, u.y);
            for(i=0;i<4;i++){
                v.x=u.x+xdir[i];
                v.y=u.y+ydir[i];
                if(v.x>=0 && v.x<row && v.y>=0 && v.y<col
                && grid[v.x][v.y]!='#' && grid[v.x][v.y]!='F'){
                    grid[v.x][v.y]='F';
                    fire.push(v);
                }
            }
            
            temp.pop();
        }
    }
    
    return -1;
}

void input(){
    int i, j;
    
    joex=joey=-1;
    std::scanf("%d%d", &row, &col);
    init(row, col);
    for(i=0;i<row;i++){
        std::scanf("%s", grid[i]);
        
        for(j=0;grid[i][j];j++){
            if(joex==-1 && grid[i][j]=='J') joex=i, joey=j;
        }
    }
    
  //  std::printf("joe : (%d %d), fire : (%d %d)\n", joex, joey, fx, fy);
}

int main(){
    int test;
    long ans;
    
    while(std::scanf("%d", &test)!=EOF){
        while(test--){
            input();
            ans=bfs();
            if(ans==-1) std::printf("IMPOSSIBLE\n");
            else std::printf("%ld\n", ans);
        }
    }
    
    return 0;
}
