#include<stdio.h>
#define MAX 100
#define INF 1<<30

long dis[MAX+2][MAX+2];
long edges[MAX*(MAX+1)+3][2], edge, test;

void init(int N){
    int i, j;
    
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            dis[i][j]=INF;
    
    for(i=0;i<edge;i++) dis[edges[i][0]][edges[i][1]]=1;
}

void floyd_warshall(int N){
    int i, j, k;
    
    for(k=1;k<=N;k++)
        for(i=1;i<=N;i++)
            for(j=1;j<=N;j++)
                if(dis[i][k]!=INF && dis[k][j]!=INF)
                    if(dis[i][j]>dis[i][k]+dis[k][j])
                        dis[i][j]=dis[i][k]+dis[k][j];
}

void output(int N){
    int i, j;
    long totldis=0, paths=0;
    
    for(i=1;i<=N;i++)
        for(j=1;j<=N;j++)
            if(dis[i][j]!=INF && i!=j) totldis+=dis[i][j], paths++;
    
    printf("Case %ld: average length between pages = %.3lf clicks\n", ++test, totldis*1.0/paths);
}

int main(){
    int i, u, v, max=0;
    
    while(scanf("%d%d", &u, &v)!=EOF){
        if(!edge && !u && !v) break;
        
        if(!u && !v){
            init(max);
            floyd_warshall(max);
            output(max);
            edge=max=0;
        }
        else{
            edges[edge][0]=u, edges[edge][1]=v;
            edge++;
            max=(max>u)? max :u;
            max=(max>v)? max :v;
        }
    }
    
    return 0;
}
