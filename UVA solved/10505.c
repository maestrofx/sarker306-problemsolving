#include<stdio.h>
#include<stdbool.h>

#define WHITE 'w'
#define GRAY 'g'
#define BLACK 'b'
#define MAXNODE 205

char edges[MAXNODE][MAXNODE*2];
char visited[MAXNODE];
char color[MAXNODE], flag;
int node, blacked, whited, max;

void dfs(int u){
    int i, v;
    
    visited[u]=GRAY;
    for(i=1;i<=node;i++){
        if(edges[u][i]==0) continue;
        v=i;
        if(color[v]){
            if(color[u]==color[v]){
                flag=0;
            }
        }
        else{
            color[v]=(color[u]==WHITE)? BLACK : WHITE;
            if(color[v]==BLACK) blacked++;
            else whited++;
            dfs(v);
        }
    }
    
    visited[u]=BLACK;
}

void check_bipartite(){
    int i;
    
    max=0;
    for(i=1;i<=node;i++){
        flag=1;
        if(color[i]==0){
            blacked=whited=0;
            color[i]=WHITE;
            visited[i]=1;
            whited++;
            dfs(i);
            if(flag==1){
                max+=(blacked>whited)?blacked:whited;
            }
        }
    }
}

int main(){
    int edge_num, x, y, i, j, k, test;
    
    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d", &node);
            
            for(i=0;i<=node;i++){
                visited[i]=color[i]=0;
                for(j=0;j<=node;j++) edges[i][j]=0;
            }
            
            for(x=1;x<=node;x++){
                scanf("%d", &edge_num);
                for(;edge_num;edge_num--){
                    scanf("%d", &y);
                    if(y>node || y<=0) continue;
                    edges[x][y]=1;
                    edges[y][x]=1;
                }
            }
            
            check_bipartite();
            printf("%d\n", max);
        }
    }
    
    return 0;
}
