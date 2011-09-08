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

	printf("%ld\n", cost_tree);
	return cost_tree;
}

int main(){
	long test, N, M, K, i, j;
	pos x;
	edge xx;

    for(test=1;  ; test++){
        if(scanf("%ld", &N)==EOF) break;
        if(test>1) printf("\n");
        for(j=1;j<N;j++) scanf("%ld%ld%ld", &edges[0].u, &edges[0].v, &edges[0].cost);
        scanf("%ld", &K);
        for(j=0; j<K; j++) scanf("%ld%ld%ld",&tmpp[j].u, &tmpp[j].v, &tmpp[j].cost);
        scanf("%ld", &M);
        for(j=0; j<M; j++) scanf("%ld%ld%ld",&edges[j].u, &edges[j].v, &edges[j].cost);
        init(N);
        mst(N, M);
        for(j=0;j<K;j++) edges[j+M]=tmpp[j];
        init(N);
        mst(N, M+K);
    }

	return 0;
}
