#include<stdio.h>
#define MAXPOINT 30005

long parent[MAXPOINT];
long rank[MAXPOINT];
long nodes, edges;

void init(long N){
	long i;
	for(i=0;i<=N;i++) parent[i]=i, rank[i]=1;
}

long find(long x){
    if(x!=parent[x]) parent[x]=find(parent[x]);
    return parent[x];
}

void link(long x,long y){
    if(rank[x]>rank[y]){
        rank[x]+=rank[y];
        parent[y]=x;
    }
    else{
		rank[y]+=rank[x];
		parent[x]=y;
    }
}

int input(void){
    long x, y, i, a, b;
    
    scanf("%ld%ld", &nodes, &edges);
    init(nodes);
    for(i=0;i<edges;i++){
        scanf("%ld%ld", &x, &y);
        a=find(x), b=find(y);
        if(a!=b) link(a, b);
    }
    
    return 1;
}

void output(void){
    long max=1, i;
    
    if(edges) for(i=1;i<=nodes;i++){
        max=(max>rank[i])? max:rank[i];
    }
    printf("%ld\n", max);
}

int main(){
    long test;
    
    scanf("%ld", &test);
    while(test--){
        input();
        output();
    }
    
    return 0;
}
