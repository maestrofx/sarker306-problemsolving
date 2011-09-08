.#include<stdio.h>
#define INF 1<<14

int n;
int distance[12][12], parent[12][12];

void init(int grid[][12], int par[][12], int n){
    int i, j;
    
    for(i=0;i<=n;i++){
        for(j=0;j<=n;j++){
            par[i][j]=grid[i][j]=INF;
        }
    }
}

void input(int grid[][12], int par[][12], int n){
    int i, v, w, nn;
    
    for(i=1;i<=n;i++){
        scanf("%d", &nn);
        
        while(nn--){
            scanf("%d%d", &v, &w);
            grid[i][v]=w;
            par[i][v]=v;
        }
    }
}

void print_matrix(int grid[][12], int n){
    int i, j;
    
    puts("------------------------------");
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++) printf("%6d ", grid[i][j]);
        puts("");
    }
    puts("------------------------------");
}

void floyd_warshall(int grid[][12], int par[][12], int n){
    int i, j, k;
    
    for(k=1;k<=n;k++){
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                if(grid[i][k]!=-1 && grid[k][j]!=-1 && grid[i][j]>grid[i][k]+grid[k][j]){
                    grid[i][j]=grid[i][k]+grid[k][j];
                    par[i][j]=par[i][k];
                }
            }
        }
    }
}

void print_path(int u, int v, int par[][12]){
    if(u==v) return;
    printf(" %d", u);
    print_path(par[u][v], v, par);
}

void query(int _case, int grid[][12], int par[][12]){
    int u, v;
    
    scanf("%d%d", &u, &v);
    if(grid[u][v]!=INF){
        printf("Case %d: Path =", _case);
        print_path(u, v, par);
        printf(" %d; %d second delay\n", v, grid[u][v]);
    }
}

int main(){
    int cases=1;
    
    while(scanf("%d", &n)!=EOF && n>0){
        init(distance, parent, n);
        input(distance, parent, n);
        floyd_warshall(distance, parent, n);
        query(cases++, distance, parent);
    }
    
    return 0;
}
