#include<stdio.h>
#include<string.h>
#define MAXNODE 302
#define QUEUESIZE 300000

int n;
int distance[MAXNODE];
int adj[MAXNODE][MAXNODE];
int degree[MAXNODE], parent[MAXNODE];

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
    for(i=0;i<=n;i++) distance[i]=-1, parent[i]=-1;
    distance[from]=0;
    push(from);
}

void print_path(int from){
    if(parent[from]!=-1){
        print_path(parent[from]);
        printf(" %d", from);
    }
    else printf("%d", from);
}

int bfs(int from, int to){
    int u, v, i;
    
    bfs_init(from);
    
    while(head!=tail){
        u=pop();
        if(u==to){
            print_path(u);
            puts("");
            return distance[u];
        }
        for(i=0;i<degree[u];i++){
            v=adj[u][i];
            if(distance[v]==-1){
                distance[v]=distance[u]+1;
                parent[v]=u;
                push(v);
            }
        }
    }
    
    return -1;
}

int main(void){
    int test, k;
    int m, p, i, u, v;
    long cost;
    char input[10000], *ptr;
    
    while(scanf("%d", &n)!=EOF){
        graph_init();
        printf("-----\n");
        getchar();

        for(i=0;i<n;i++){
            gets(input);
            ptr=strtok(input, "-,");
            sscanf(ptr, "%d", &u);
            
            while((ptr=strtok(0, "-,"))!=0){
                sscanf(ptr, "%d", &v);
                adj[u][degree[u]++]=v;
            }
        }
        
        if(scanf("%d", &m)==EOF) break;
        while(m--){
            scanf("%d%d", &u, &v);
            cost=bfs(u, v);
            
            if(cost==-1) printf("connection impossible\n");
        }
    }
    
    return 0;
}
