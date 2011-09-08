#include<stdio.h>
#include<string.h>
#define MAXNODE 2502
#define QUEUESIZE 3000000

int n;
int distance[MAXNODE], days[MAXNODE];
int adj[MAXNODE][MAXNODE];
int degree[MAXNODE];

int queue[QUEUESIZE+1];
long head, tail;

void push(int x){
    queue[tail]=x;
    if(tail==QUEUESIZE) tail=0;
    else tail++;
}

int pop(void){
    int x=queue[head];
    if(head==QUEUESIZE) head=0;
    else head++;
    return x;
}

void graph_init(void){
    int i, j;
    
    for(i=0;i<=n;i++) degree[i]=0;
}

void bfs_init(int from){
    int i;
    
    head=tail=0;
    for(i=0;i<=n;i++) distance[i]=-1, days[i]=0;
    distance[from]=0;
    push(from);
}

int bfs(int from){
    int u, v, i;
    
    bfs_init(from);
    
    while(head!=tail){
        u=pop();
        
        for(i=0;i<degree[u];i++){
            v=adj[u][i];
            if(distance[v]==-1){
                distance[v]=distance[u]+1;
                days[distance[v]]++;
                push(v);
            }
        }
    }
    
    for(i=1, u=v=0;i<n;i++){
        if(u<days[i]) u=days[i], v=i;
    }
    
    if(u==0 && v==0) return -1;
    printf("%d %d\n", u, v);
    return 0;
}

int main(void){
    int test, k;
    int m, p, i, u, v;
    long res;
    char input[10000], *ptr;
    
    while(scanf("%d", &n)!=EOF){
        graph_init();

        for(i=0;i<n;i++){
            scanf("%d", &degree[i]);
            for(m=0;m<degree[i];m++){
                scanf("%d", &v);
                adj[i][m]=v;
            }
        }
        
        if(scanf("%d", &m)==EOF) break;
        while(m--){
            scanf("%d", &u);
            res=bfs(u);
            
            if(res==-1) printf("0\n");
        }
    }
    
    return 0;
}
