#include<stdio.h>

#define SIZE 105
char adj[SIZE][SIZE];
char visited[SIZE+1][SIZE];
char allowed[SIZE];
int n;

int queue[SIZE+1];
int head, tail;

int dequeue(){
    int x=queue[head];
    if(head==SIZE) head=0;
    else head++;
    return x;
}

void enqueue(int x){
    queue[tail]=x;
    if(tail==SIZE) tail=0;
    else tail++;
}

void init(){
    register int i, j;

    for(i=0;i<=n;i++)
        for(allowed[i]=1, j=0;j<n;j++)
            visited[i][j]=0;
}

void bfs(int s, int not_allowed){
    register int u, i;

    head=tail=0, visited[not_allowed][s]=1;
    enqueue(s);
    while(head!=tail){
        u=dequeue();
        for(i=0;i<n;i++){
            if(adj[u][i] && allowed[i] && visited[not_allowed][i]==0)
                visited[not_allowed][i]=1, enqueue(i);
        }
    }
}

void traverse(){
    register int i;

    for(i=1;i<=n;i++){
        allowed[i]=0;
        bfs(0, i);
        allowed[i]=1;
    }
}

void output(int test){
    register int i, j;

    printf("Case %d:\n", test);
    putchar('+');
    for(j=1;j<2*n;j++) putchar('-');
    putchar('+');
    puts("");
    for(i=0;i<n;i++){
        putchar('|');
        for(j=0;j<n;j++)
            printf("%c|", (visited[i][j]^visited[n][j]) ? 'Y' : 'N');
        puts("");
        putchar('+');
        for(j=1;j<2*n;j++) putchar('-');
        putchar('+');
        puts("");
    }
}

int main(){
    int test;
    register int i, j, k;

    while(scanf("%d", &test)!=EOF){
        for(k=1;k<=test;k++){
            scanf("%d", &n);
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    scanf("%d", &adj[i][j]);

            init();
            traverse();
            output(k);
        }
    }

    return 0;
}
