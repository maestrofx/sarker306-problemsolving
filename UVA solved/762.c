#include<stdio.h>
#define MAXNODE 700
#define QUEUESIZE 300000

int index[700], cities[700];
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
    int i;
    
    for(i=0;i<=676;i++) index[i]=cities[i]=-1;
}

void bfs_init(int from){
    int i;
    
    head=tail=0;
    for(i=0;i<=n;i++){
        distance[i]=-1;
        parent[i]=-1;
    }
    
    distance[from]=0;
    push(from);
}

void print_path(int u){
    int par=parent[u];
    
    if(par!=-1){
        print_path(par);
        printf("%c%c %c%c\n", cities[par]/26+'A', cities[par]%26+'A', 
            cities[u]/26+'A', cities[u]%26+'A');
    }
}

int bfs(int from, int to){
    int u, v, i;
    
    bfs_init(from);
    
    while(head!=tail){
        u=pop();
        if(u==to){
            print_path(u);
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
    int test=0, k;
    int m, p, i, u, v;
    long cost;
    char city1[5], city2[5];
    
    while(scanf("%d", &m)!=EOF){
        n=0;
        graph_init();
        
        for(i=0;i<m;i++){
            scanf("%s%s", city1, city2);
            u=26*(city1[0]-'A')+(city1[1]-'A');
            v=26*(city2[0]-'A')+(city2[1]-'A');
            
            if(u<676){
                if(index[u]==-1){
                    index[u]=n;
                    cities[n++]=u;
                }
                u=index[u];
            }
            else u=-1;
            
            if(v<676){
                if(index[v]==-1){
                    index[v]=n;
                    cities[n++]=v;
                }
                v=index[v];
            }
            else v=-1;
            
            if(u!=-1 && v!=-1){
                adj[u][degree[u]++]=v;
                adj[v][degree[v]++]=u;
            }
        }
        
        cost=-1;
        scanf("%s%s", city1, city2);
        u=26*(city1[0]-'A')+(city1[1]-'A');
        v=26*(city2[0]-'A')+(city2[1]-'A');
        
        if(u<676 && index[u]!=-1) u=index[u];
        else u=-1;
        if(v<676 && index[v]!=-1) v=index[v];
        else v=-1;
        
        if(test) puts("");
        test++;
        if(u==-1 || v==-1) cost=-1;
        else cost=bfs(u, v);
        
        if(cost==-1) printf("No route\n");
        
        for(i=0;i<=n;i++) degree[i]=0;
    }
    
    return 0;
}
