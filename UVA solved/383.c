#include<stdio.h>
#define MAXNODE 35
#define QUEUESIZE 30000

int index[700];
int n;
int distance[MAXNODE];
int adj[MAXNODE][MAXNODE];
int degree[MAXNODE];

int queue[QUEUESIZE+1], head, tail;

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
    
    for(i=0;i<=676;i++) index[i]=-1;
    for(i=0;i<=n;i++) degree[i]=0;
}

void bfs_init(int from){
    int i;
    
    head=tail=0;
    for(i=0;i<=n;i++) distance[i]=0;
    push(from);
}

int bfs(int from, int to){
    int u, v, i;
    
    bfs_init(from);
    
    while(head!=tail){
        u=pop();
        if(u==to) return distance[u];
        for(i=0;i<degree[u];i++){
            v=adj[u][i];
            if(distance[v]==0){
                distance[v]=distance[u]+1;
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
    char city1[5], city2[5];
    
    while(scanf("%d", &test)!=EOF){
        printf("SHIPPING ROUTES OUTPUT\n");
        for(k=1;k<=test;k++){
            scanf("%d%d%d", &n, &m, &p);
            
            graph_init();
            for(i=0;i<n;i++){
                scanf("%s", city1);
                u=26*(city1[0]-'A')+(city1[1]-'A');
                if(index[u]==-1) index[u]=i;
            }
            
            for(i=0;i<m;i++){
                scanf("%s%s", city1, city2);
                u=26*(city1[0]-'A')+(city1[1]-'A');
                v=26*(city2[0]-'A')+(city2[1]-'A');
                
                if(u<676) u=index[u];
                else u=-1;
                if(v<676) v=index[v];
                else v=-1;
                if(u!=-1 && v!=-1){
                    adj[u][degree[u]++]=v;
                    adj[v][degree[v]++]=u;
                }
            }
            
            printf("\nDATA SET  %d\n\n", k);
            for(i=0;i<p;i++){
                cost=-1;
                scanf("%d%s%s", &m, city1, city2);
                u=26*(city1[0]-'A')+(city1[1]-'A');
                v=26*(city2[0]-'A')+(city2[1]-'A');
                
                if(u<676) u=index[u];
                else u=-1;
                if(v<676) v=index[v];
                else v=-1;
                
                if(u==-1 || v==-1) cost=-1;
                else cost=bfs(u, v);
                
                if(cost!=-1) printf("$%ld\n", cost*100*m);
                else printf("NO SHIPMENT POSSIBLE\n");
            }
        }
        
        printf("\nEND OF OUTPUT\n");
    }
    
    return 0;
}
