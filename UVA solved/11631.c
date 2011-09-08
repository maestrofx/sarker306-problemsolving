#include<stdio.h>
#include<stdlib.h>
#define MAXPOINT 1000005
#define MAXEDGE 10000005

typedef long pos;

typedef struct{
	long u, v;
	long cost;
}edge;

pos vertices[MAXPOINT];
long rank[MAXPOINT];
long parent[MAXPOINT];
edge edges[MAXEDGE];
edge tmpp[15];

void init(long N){
	long i;
	for(i=0;i<=N;i++) parent[i]=i, rank[i]=0;
}

int cmp(const void *x,const void *y){
    edge *a=(edge *)x;
    edge *b=(edge *)y;
    if(a->cost-b->cost) return (a->cost>b->cost)?1:-1;
	return 0;
}

int find(int x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link(int x,int y){
    if(rank[x]>rank[y]) parent[y]=x;
    else{
		if(rank[x]==rank[y]) rank[y]++;
		parent[x]=y;
    }
}

long mst(long N, long M){
    long i, j, x, y, edge_tree=0, cost_tree=0;

    qsort(edges, M, sizeof(edge), cmp);
	for(i=0;i<M;i++){
        if(edge_tree==N-1) break;
        x=find(edges[i].u), y=find(edges[i].v);
        if(x!=y){
            link(x,y);
            edge_tree++, cost_tree+=edges[i].cost;
        }
    }

	return cost_tree;
}

int main(){
	long test, N, M, K, i, j, total_cost;
	pos x;
	edge xx;

    while(scanf("%ld%ld", &N, &M)!=EOF){
        if(N==0 && M==0) break;
        
        for(j=0, total_cost=0; j<M; j++){
            scanf("%ld%ld%ld",&edges[j].u, &edges[j].v, &edges[j].cost);
            total_cost+=edges[j].cost;
        }
        
        init(N);
        printf("%ld\n", total_cost-mst(N, M));
    }

	return 0;
}
