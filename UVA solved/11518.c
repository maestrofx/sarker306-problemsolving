#include<stdio.h>
#define WHITE 0
#define GRAY 1
#define BLACK 2
#define MAX 10005

typedef struct{
    int count, adj[MAX+2];
}adj;

adj matrix[MAX+2];
char color[MAX+2];
int queue[MAX*2+2], head, tail;

void initgraph(int n){
    int i;

    for(i=0;i<=n;i++) color[i]=WHITE, matrix[i].count=0;
}

int pop(void){
    int x=queue[head];
    if(head==MAX*2) head=0;
    else head++;
    return x;
}

void push(int x){
    queue[tail]=x;
    if(tail==MAX*2) tail=0;
    else tail++;
}

void bfs(int source){
    int i, v, u;

    head=tail=0;
    push(source);
    color[source]=GRAY;
    while(head!=tail){
        u=pop();
        for(i=0;i<matrix[u].count;i++){
            v=matrix[u].adj[i];
            if(color[v]==WHITE)  push(v), color[v]=GRAY;
        }

        color[u]=BLACK;
    }
}

int main(){
    int test, n, m, l, i, u, v, fallen;

    while(scanf("%d", &test)!=EOF){
        while(test--){
            scanf("%d%d%d", &n, &m, &l);
            initgraph(n);
            for(i=0;i<m;i++){
                scanf("%d%d", &u, &v);
                matrix[u].adj[matrix[u].count++]=v;
            }

            for(i=0;i<l;i++){
                scanf("%d", &u);
                if(color[u]==WHITE) bfs(u);
            }

            for(i=1, fallen=0;i<=n;i++) if(color[i]==BLACK) fallen++;
            printf("%d\n", fallen);
        }
    }

    return 0;
}

