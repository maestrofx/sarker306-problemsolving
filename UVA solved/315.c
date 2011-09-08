#include<stdio.h>

#define SIZE 102
#define WHITE 'w'
#define BLACK 'b'
#define GRAY 'g'
#define NUL -1

typedef struct{
    int n;
    int adj[SIZE];
    char is_there[SIZE];
}adjacency;

char color[SIZE];
int finish[SIZE], start[SIZE], parent[SIZE], low[SIZE];
int time;

adjacency adj[SIZE];
int N;

void graph_init(){
    int i, j;
    
    for(i=1;i<=N;i++){
        color[i]=WHITE;
        adj[i].n=0;
        start[i]=0;
        finish[i]=0;
        low[i]=0;
        parent[i]=NUL;
        
        for(j=0;j<SIZE;j++) adj[i].is_there[j]=0;
    }
}

void add_edge(int u, int v){
    if(adj[u].is_there[v]==0){
        adj[u].adj[adj[u].n++]=v;
        adj[u].is_there[v]=1;
    }
    if(adj[v].is_there[u]==0){
        adj[v].adj[adj[v].n++]=u;
        adj[v].is_there[u]=1;
    }
}

void dfs(int node){
    int i, v;
    
    color[node]=GRAY;
    low[node]=start[node]=++time;
    
    for(i=0;i<adj[node].n;i++){
        v=adj[node].adj[i];
        if(color[v]==WHITE){
            parent[v]=node;
            dfs(v);
            low[node]=(low[node]<low[v])?low[node]:low[v];
        }
        else if(v!=parent[node]){
            low[node]=(low[node]<start[v])?low[node]:start[v];
        }
    }
    
    color[node]=BLACK;
    finish[node]=++time;
}

void dfs_visit(){
    int i;
    
    for(i=1, time=0;i<=N;i++){
        if(color[i]==WHITE){
            parent[i]=i;
            dfs(i);
        }
    }
}

void articulation_point(){
    int u, i, v, is_root, children_of_root, count=0;
    
    dfs_visit();
    
    for(u=1;u<=N;u++){
        is_root=0;
        if(parent[u]== u ){
            is_root=1;
            children_of_root=0;
        }
        
        for(i=0;i<adj[u].n;i++){
            v=adj[u].adj[i];
            if(is_root && parent[v]==u && v!=u) children_of_root++;
            
            if(low[v]>=start[u] && parent[v]==u){
                if(!is_root || children_of_root>1) break;
            };
        }
        
        if(i!=adj[u].n){
            count++;
        }
    }
    
    printf("%d\n", count);
}

int input(){
    int i, j, x, y;
    
    if(scanf("%d", &N)==EOF) return 0;
    if(N==0) return 0;
    graph_init();
    
    while(scanf("%d", &x)!=EOF && x>0){
        while(getchar()!='\n'){
            scanf("%d", &y);
            if(x>0 && x<=N && y>0 && y<=N) add_edge(x, y);
        }
    }
    
    return 1;
}

int main(){
    while(input()) articulation_point();
    
    return 0;
}
