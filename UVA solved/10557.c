#include <stdio.h>

#define SIZE 105
#define INF 1<<30

int adj[SIZE*SIZE][2], mat[SIZE][SIZE];
long playr[SIZE], energy[SIZE];
int n, edges, True;

void init(){
    int i, j;

    for(i=1;i<=n;i++) playr[i]=INF;

    True++;
    edges=0;
    playr[1]=-100; /* player starts with 100 energy pts. */
}

void relax(int u, int v, long w){
    if(playr[v]>playr[u]+w && playr[u]+w<0) playr[v]=playr[u]+w;
}

int bellman_ford(){
    int u, v, i, j;

    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            for(u=1;u<=n;u++)
                if(mat[j][i]==True && mat[i][u]==True) mat[j][u]=True;

    if(mat[1][n]!=True){
        /*printf("Pouchate parilo na\n");*/
        return 1;
    }

    for(i=1;i<n;i++){
        for(j=0;j<edges;j++){
            u=adj[j][0], v=adj[j][1];
            relax(u, v, energy[v]);
        }
    }

    if(playr[n]<0){
        /*printf("Dom furaynai\n");*/
        return 0;
    }

    for(j=0;j<edges;j++){
        u=adj[j][0], v=adj[j][1];
        if(mat[1][u]==True && mat[u][n]==True && playr[u]<0 && playr[v]<0 && playr[v]>playr[u]+energy[v]){
            /*printf("Cycle paisi\n");*/
            return 0;
        }
    }

   /* for(i=1;i<n;i++) if(mat[1][i]==True && mat[i][n]==True && playr[i]>=0) return 1;*/

    return 1;
}

int main(){
    int i, j, v;

    while(scanf("%d", &n)!=EOF && n!=-1){
        init();
        for(i=1;i<=n;i++){
            scanf("%ld%d", &energy[i], &j);
            energy[i]=-energy[i];
            while(j--){
                scanf("%d", &v);
                adj[edges][0]=i;
                adj[edges++][1]=v;
                mat[i][v]=True;
            }
        }

        if(bellman_ford()) puts("hopeless");
        else puts("winnable");
    }

    return 0;
}
